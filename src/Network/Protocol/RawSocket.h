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

protected:
  void setTimeval(int ms);

protected:
  int m_socket = -1;

};

#endif // RAWSOCKET_H
