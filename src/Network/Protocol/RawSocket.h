#ifndef RAWSOCKET_H
#define RAWSOCKET_H

#include <unistd.h>

class RawSocket
{
public:
  RawSocket(){};
  virtual ~RawSocket();

  virtual void createSocket(int domain, int type, int protocol);
  virtual void closeSockets();

  // virtual void send(const void* data, size_t len) = 0;
  // virtual ssize_t receive(void* buffer, size_t len) = 0;

protected:
  int m_socket = -1;

};

#endif // RAWSOCKET_H
