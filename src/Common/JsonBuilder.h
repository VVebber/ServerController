#ifndef JSONBUILDER_H
#define JSONBUILDER_H

#include <QJsonObject>

struct NetAdapter;
class DeviceInfo;

class JsonBuilder
{
public:
  static QJsonObject toJson(const NetAdapter& adapter);
  static QJsonObject toJson(const DeviceInfo* device);
};

#endif // JSONBUILDER_H
