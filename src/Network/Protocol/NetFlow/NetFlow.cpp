#include "NetFlow.h"

#include <sys/socket.h>
#include <netinet/in.h>


NetFlow::NetFlow()
{
  createSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

NetFlow::~NetFlow()
{

}
