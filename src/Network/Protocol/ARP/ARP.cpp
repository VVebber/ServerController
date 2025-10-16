// #include "ARP.h"

// #include "../../../Common.h"
// #include "../../../AppVariables.h"
// // #include "../../../Tasks/ObjectInfo.h"

// #include <linux/if_ether.h>
// #include <linux/if_packet.h>
// #include <arpa/inet.h>

// #include <QDebug>

// ARP::ARP()
// {
//   createSocket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
// }


// void ARP::process(class ObjectInfo& objectInfo)
// {
//   qDebug()<<Q_FUNC_INFO;
//   AppVariables& variables = AppVariables::instance();

//   QString macStr = variables.get(KEY_IF_MAC).toString();
//   QString senderIp = variables.get(KEY_CURRENT_IP).toString();

//   unsigned char senderMac[6];

//   if(!parseMacAddress(macStr, senderMac))
//   {
//     return;
//   }

//   struct sockaddr_ll devise = {};
//   devise.sll_family = AF_PACKET;
//   devise.sll_ifindex = variables.get(KEY_IF_INDEX).toInt();
//   devise.sll_halen = ETH_ALEN;
//   memset(devise.sll_addr, 0xFF, 6);


//   if(bind(m_socket, (struct sockaddr*) & devise, sizeof(struct sockaddr_ll)) < 0)
//   {
//     qWarning()<<"bind"<< strerror(errno);
//     return;
//   }

//   aprPacker apr = {};
//   apr.header.ar_hrd = htons(1);
//   apr.header.ar_pro= htons(0x0800);

//   apr.header.ar_hln = 6;
//   apr.header.ar_pln = 4;

//   apr.header.ar_op = htons(ARPOP_REQUEST);

//   inet_pton(AF_INET, senderIp.toStdString().c_str(), apr.sender_ip);
//   // inet_pton(AF_INET, objectInfo.ipData(), apr.target_ip);

//   memcpy(apr.sender_mac, senderMac, 6);
//   memset(apr.target_mac, 0x00, 6);

//   char packet[60];
//   memcpy(packet, BROADCAST_MAC, 6);
//   memcpy(packet + 6, senderMac, 6);
//   packet[12] = 0x08;
//   packet[13] = 0x06;
//   memcpy(packet + 14, &apr, sizeof(apr));

//   int ret = sendto(m_socket, packet, sizeof(packet),0, (struct sockaddr*) &devise, sizeof(devise));

//   if(ret == -1)
//   {
//     qWarning()<<"sendto"<< strerror(errno);
//     return;
//   }


//   char buf[1024];
//   struct sockaddr_ll addr;
//   int date_lenght = recvfrom(m_socket, buf, sizeof(buf),0,  NULL, NULL);
//   if(date_lenght != -1)
//   {
//     struct ethhdr* eth = (struct ethhdr*)buf;

//     if (ntohs(eth->h_proto) == ETH_P_ARP)
//     {
//       struct aprPacker *arp_resp = (struct aprPacker*)((char*)eth + sizeof(struct ethhdr));
//       if (ntohs(arp_resp->header.ar_op) == ARPOP_REPLY)
//       {
//         // objectInfo.setMacAddress(arp_resp->target_mac);
//       }
//     }
//   }
//   else {
//     perror("recvfrom()");
//     return;
//   }
// }
