#include "Common.h"

#include "Models/DeviceInfo.h"

#include <QStringList>
#include <QDebug>

bool parseMacAddress(const QString& macStr, unsigned char mac[6])
{
  QStringList macParts = macStr.split(':');

  if (macParts.size() != 6) {
      qWarning() << "Некорректный MAC-адрес";
      return false;
  }

  for (int i = 0; i < 6; ++i) {
      bool ok;
      mac[i] = macParts[i].toUInt(&ok, 16);
      if (!ok) {
          qWarning() << "Ошибка конвертации части MAC:" << macParts[i];
          return false;
      }
  }
  return true;
}

int find(QList<DeviceInfo*> devices, DeviceInfo* devic)
{
  int i = -1;

  if(!devic)
    return i;

  for(auto& device : devices)
  {
    i++;
    if(device->getIpv4() == devic->getIpv4())
    {
      break;
    }
  }
  return i;
}
