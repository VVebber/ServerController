#ifndef NETFLOW_H
#define NETFLOW_H

#include "../RawSocket.h"

class NetFlow : public RawSocket
{
public:
  NetFlow();
  ~NetFlow();
};

#endif // NETFLOW_H
