#ifndef NETADAPTER_H
#define NETADAPTER_H

#include <QString>
#include <QStringList>

struct NetAdapter
{
  QString name;
  QString mac;
  QString ipv4;
  bool isAtive;

  void setIp(QString prefixLengthStr)
  {
    QStringList octets = ipv4.split(".");

    bool ok = false;
    int prefixLength = prefixLengthStr.toInt(&ok);

    if(!ok)
      return;

    if(prefixLength == 24)
    {
      octets[3] = "%0";
    }
    else if(prefixLength == 16)
    {
      octets[2] = "%0";
      octets[3] = "%1";
    }
    else if (prefixLength == 8) {
      octets[1] = "%0";
      octets[2] = "%1";
      octets[3] = "%2";
    }

    ipv4 = octets.join(".");
  }
};

#endif // NETADAPTER_H
