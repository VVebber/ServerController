#include "ICMP.h"

#include "../../../Common.h"
#include "../../../AppVariables.h"
// #include "../../../Tasks/ObjectInfo.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <netinet/ip_icmp.h>

#include <arpa/inet.h>

#include <QDebug>

static const size_t sizePacket = 64;
static const size_t sizeBuffer = 1024;

static const int countPackets = 2;

ICMP::ICMP()
{
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 200000; //todo:

  createSocket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
  setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}

ICMP::~ICMP(){}

uint16_t ICMP::checksum(void *data, int len) {
  uint16_t *buf = (uint16_t *)data;
  uint32_t sum = 0;

  while (len > 1) {
    sum += *buf++;
    len -= 2;
  }

  if (len == 1) {
    sum += *(uint8_t *)buf;
  }

  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);

  return ~sum;
}

struct icmphdr* ICMP::createPacket(char* packet)
{
  struct icmphdr* icmp = (struct icmphdr*) packet;
  icmp->type = ICMP_ECHO;
  icmp->code = 0;
  icmp->un.echo.id = getppid();
  icmp->un.echo.sequence = htons(1);
  icmp->checksum = 0;

  icmp->checksum = checksum(icmp, sizePacket);

  return icmp;
}

void ICMP::process()
{
  qDebug()<<Q_FUNC_INFO;
  sockaddr_in toAddr{};
  toAddr.sin_family = AF_INET;
  toAddr.sin_port = htons(0);


  char packet[sizePacket];
  struct icmphdr* icmp = createPacket(packet);

  for(int i = 1; i < 10; i++)
  {
    std::string ipStr = "192.168.1." + std::to_string(i);
    inet_pton(AF_INET, ipStr.c_str(), &toAddr.sin_addr);

    uint64_t totalTime = 0;
    int successReplies = 0;

    for(int j = 0; j < countPackets; j++)
    {
      ssize_t sent = sendto(m_socket, packet, sizePacket, 0, (struct sockaddr *)&toAddr, sizeof(toAddr));

      if (sent < 0) {
        qWarning()<<"sendto failed"<< strerror(errno);
        continue;
      }

      char buffer[sizeBuffer];
      uint64_t msBefore = std::chrono::duration_cast<std::chrono::milliseconds>
                          (std::chrono::system_clock::now().time_since_epoch()).count();

      int date_length = recv(m_socket, buffer, sizeBuffer, 0);

      uint64_t msAfter = std::chrono::duration_cast<std::chrono::milliseconds>
                         (std::chrono::system_clock::now().time_since_epoch()).count();

      if(date_length != -1)
      {
        icmphdr *res = (struct icmphdr*) buffer;
        if(res->type == ICMP_ECHOREPLY)
        {
          totalTime += (msAfter - msBefore);
          successReplies++;
        }
      }
    }
    // if (successReplies > 0)
    // {
    //   qDebug() << "IP:" << QString::fromStdString(ipStr)
    //            << "Avg Time:" << totalTime / successReplies << "ms";
    //   QVariant var = AppVariables::instance().get(KEY_OBJECT_INFO);
    //   QList<ObjectInfo>* objectList = var.value<QList<ObjectInfo>*>();

    //   if(!objectList->contains(ipStr))
    //   {
    //     ObjectInfo data(ipStr);
    //     data.updateICMPStatus(true);
    //     objectList->append(data);
    //   }
    // }
  }
}

//Работа утилиты traceroute
