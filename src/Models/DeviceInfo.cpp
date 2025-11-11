#include "DeviceInfo.h"


DeviceInfo::DeviceInfo()
{

}

void DeviceInfo::setIpv4(const QString ipv4)
{
  m_ipv4 = ipv4;
}

void DeviceInfo::setMac(const QString mac)
{
  m_mac = mac;
}

void DeviceInfo::setAdapterName(const QString adapterName)
{
  m_adapterName = adapterName;
}


const QString DeviceInfo::getIpv4() const
{
  return m_ipv4;
}

const QString DeviceInfo::getMac() const
{
  return m_mac;
}

const QString DeviceInfo::getAdapterName() const
{
  return m_adapterName;
}
