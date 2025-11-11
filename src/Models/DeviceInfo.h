#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>

class DeviceInfo : public QObject
{
  Q_OBJECT
public:
  DeviceInfo();

  // void setUserName(const QString userName);
  // void setPassword(const QString password);
  void setIpv4(const QString ipv4);
  void setMac(const QString mac);
  void setAdapterName(const QString adapterName);

  const QString getIpv4() const;
  const QString getMac() const;
  const QString getAdapterName() const;

private:
  QString m_adapterName;
  QString m_userName;
  QString m_password;
  QString m_ipv4;
  QString m_mac;

  friend class WinRM;
};

#endif // DEVICEINFO_H
