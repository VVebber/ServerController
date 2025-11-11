#include "ARP_Ping.h"

#include "../../../Common.h"
#include "../../../AppVariables.h"
#include "../../../Models/NetAdapter.h"

#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>

#include <QDebug>

ARP_Ping::ARP_Ping()
{
  qDebug()<<Q_FUNC_INFO;

  createSocket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
  setTimeval(200);
}


ArpPingRes ARP_Ping::process(const char* ip, struct NetAdapter& adapter)
{
  ArpPingRes res;
  res.ip = new char[strlen(ip) + 1];
  std::strcpy(res.ip, ip);

  AppVariables& variables = AppVariables::instance();

  QString senderIp = variables.getCurrentIp();

  unsigned char senderMac[6];


  if(!parseMacAddress(adapter.mac, senderMac))
  {
    return ArpPingRes();
  }

  struct sockaddr_ll devise = {};
  devise.sll_family = AF_PACKET;
  devise.sll_ifindex = adapter.ifIndex;
  devise.sll_halen = ETH_ALEN;
  memset(devise.sll_addr, 0xFF, 6);

  if(bind(m_socket, (struct sockaddr*) & devise, sizeof(struct sockaddr_ll)) < 0)
  {
    qWarning()<<"bind: "<< strerror(errno);
    return ArpPingRes();
  }

  arpPacker arp = {};
  arp.header.ar_hrd = htons(1);
  arp.header.ar_pro= htons(0x0800);

  arp.header.ar_hln = 6;
  arp.header.ar_pln = 4;

  arp.header.ar_op = htons(ARPOP_REQUEST);

  inet_pton(AF_INET, senderIp.toStdString().c_str(), arp.sender_ip);
  inet_pton(AF_INET, ip, arp.target_ip);

  memcpy(arp.sender_mac, senderMac, 6);
  memset(arp.target_mac, 0x00, 6);

  char packet[60];
  memcpy(packet, BROADCAST_MAC, 6);
  memcpy(packet + 6, senderMac, 6);
  packet[12] = 0x08;
  packet[13] = 0x06;
  memcpy(packet + 14, &arp, sizeof(arp));

  int ret = sendto(m_socket, packet, sizeof(packet), 0, (struct sockaddr*) &devise, sizeof(devise));

  if(ret == -1)
  {
    qWarning()<<"sendto"<< strerror(errno);
    return ArpPingRes();
  }


  char buf[1024];
  struct sockaddr_ll addr;

  unsigned char targetIpBytes[4];
  inet_pton(AF_INET, ip, targetIpBytes);

  while (true)
  {
    int date_lenght = recvfrom(m_socket, buf, sizeof(buf),0,  NULL, NULL);
    if(date_lenght < 0)
    {
      break;
    }

    struct ethhdr* eth = (struct ethhdr*)buf;

    if (ntohs(eth->h_proto) != ETH_P_ARP)
    {
      continue;
    }

    struct arpPacker *arp_resp = (struct arpPacker*)((char*)eth + sizeof(struct ethhdr));

    if (ntohs(arp_resp->header.ar_op) != ARPOP_REPLY)
    {
      continue;
    }

    if(memcmp(arp_resp->sender_ip, targetIpBytes, 4) != 0)
    {
      continue;
    }

    sprintf(res.mac, "%02X:%02X:%02X:%02X:%02X:%02X",
            arp_resp->sender_mac[0],
            arp_resp->sender_mac[1],
            arp_resp->sender_mac[2],
            arp_resp->sender_mac[3],
            arp_resp->sender_mac[4],
            arp_resp->sender_mac[5]);

    return res;
  }

  return ArpPingRes();
}


