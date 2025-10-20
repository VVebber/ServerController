#include "RawSocket.h"

#include <sys/socket.h>
#include <sys/unistd.h>
#include <cstring>

#include <QDebug>


RawSocket::~RawSocket()
{
  closeSockets();
}

void RawSocket::createSocket(int domain, int type, int protocol)
{
  m_socket = socket(domain, type, protocol);
  if(m_socket < 0)
  {
    qWarning() << "Socket creation failed:" << strerror(errno);
  }
}

void RawSocket::setTimeval(int ms)
{
  if(m_socket == -1)
    return;

  struct timeval tv;
  tv.tv_sec  = ms / 1000;
  tv.tv_usec = (ms % 1000) * 1000;

  setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
}

void RawSocket::closeSockets(){
  if(m_socket != -1)
  {
    close(m_socket);
    m_socket = -1;
  }
}
