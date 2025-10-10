#ifndef ICMP_H
#define ICMP_H

#include "../RawSocket.h"

#include <stdint.h>

class ICMP : public RawSocket
{
public:
  ICMP();
  ~ICMP();

  void process();

private:
  struct icmphdr* createPacket(char* packet);

private:
  uint16_t checksum(void *data, int len);
};

#endif // ICMP_H
