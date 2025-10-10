#ifndef NETADAPTER_H
#define NETADAPTER_H

#include <QString>

struct NetAdapter
{
  QString name;
  QString mac;
  bool isAtive;
};

#endif // NETADAPTER_H
