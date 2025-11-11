#include "JsonBuilder.h"

#include "../Models/NetAdapter.h"
#include "../Models/DeviceInfo.h"

QJsonObject JsonBuilder::toJson(const NetAdapter& adapter)
{
    QJsonObject obj;
    obj["name"] = adapter.name;
    obj["ipv4"] = adapter.ipv4;
    obj["mac"] = adapter.mac;
    return obj;
}

QJsonObject JsonBuilder::toJson(const DeviceInfo* device)
{
  QJsonObject obj;
  obj["adapterName"] = device->getAdapterName();
  obj["ipv4"] = device->getIpv4();
  obj["mac"] = device->getMac();

  return obj;
}

