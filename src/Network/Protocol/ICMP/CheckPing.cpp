#include "CheckPing.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#include <arpa/inet.h>

#include <QDebug>

static const size_t sizePacket = 64;
static const size_t sizeBuffer = 1024;

static const int countPackets = 2;

CheckPing::CheckPing()
{
  qDebug()<<Q_FUNC_INFO;

  createSocket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);
  setTimeval(200);
}

CheckPing::~CheckPing()
{
  qDebug()<<Q_FUNC_INFO;
}

uint16_t CheckPing::checksum(void *data, int len) {
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

#if defined(Q_OS_LINUX)
struct icmphdr* CheckPing::createPacket(char* packet)
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
#elif defined(Q_OS_MACOS)

struct icmp* CheckPing::createPacket(char* packet)
{
  struct icmp* icmpPacket = (struct icmp*) packet;
  icmpPacket->icmp_type = ICMP_ECHO;
  icmpPacket->icmp_code = 0;
  icmpPacket->icmp_hun.ih_idseq.icd_id = getppid();
  icmpPacket->icmp_hun.ih_idseq.icd_id = htons(1);
  icmpPacket->icmp_cksum = 0;

  icmpPacket->icmp_cksum = checksum(icmpPacket, sizePacket);

  return icmpPacket;
}
#endif



PingRes CheckPing::process(const char* ip)
{
  PingRes result;
  result.sent = countPackets;
  result.ip = new char[strlen(ip) + 1];
  std::strcpy(result.ip, ip);


  sockaddr_in toAddr{};
  toAddr.sin_family = AF_INET;
  toAddr.sin_port = htons(0);

  char packet[sizePacket];
#if defined(Q_OS_LINUX)
  struct icmphdr* icmpPacket = createPacket(packet);
#elif defined(Q_OS_MACOS)
  struct icmp* icmpPacket = createPacket(packet);
#endif
  inet_pton(AF_INET, ip, &toAddr.sin_addr);

  uint64_t totalTime = 0;
  int successReplies = 0;

  for(int j = 0; j < countPackets; j++)
  {
    ssize_t sent = sendto(m_socket, packet, sizePacket, 0, (struct sockaddr *)&toAddr, sizeof(toAddr));

    if (sent < 0) {
      result.errorCode = errno;
      qWarning()<<"sendto failed"<< strerror(errno);
      continue;
    }

    auto msBefore = std::chrono::steady_clock::now();
    char buffer[sizeBuffer];

#if defined(Q_OS_LINUX)
    struct icmphdr *icmpResHeader = (struct icmphdr*) buffer;
#elif defined(Q_OS_MACOS)
    struct icmp* icmpResHeader = (struct icmp*) buffer;
#endif

    int date_length = recv(m_socket, icmpResHeader, sizeBuffer, 0);

    auto msAfter = std::chrono::steady_clock::now();

    if(date_length != -1)
    {
      int type = -1;

#if defined(Q_OS_LINUX)
    type = unsigned(icmpResHeader->type);
#elif defined(Q_OS_MACOS)
      type = unsigned(icmpResHeader->icmp_type);
#endif

      if(type == ICMP_ECHOREPLY)
      {
        uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(msAfter - msBefore).count();
        totalTime += ms;
        successReplies++;

        if (result.minMs < 0 || ms < result.minMs) result.minMs = ms;
        if (result.maxMs < 0 || ms > result.maxMs) result.maxMs = ms;
      }
    }
  }

  result.received = successReplies;
  if (successReplies > 0)
  {
    return result;
  }
  return PingRes();
}

//Работа утилиты traceroute
