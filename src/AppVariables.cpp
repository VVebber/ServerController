#include "AppVariables.h"
// #include "Tasks/ObjectInfo.h"
#include "Models/NetAdapter.h"

#include <QMetaType>

// Q_DECLARE_METATYPE(QList<ObjectInfo>)

AppVariables::AppVariables()
{
  // qRegisterMetaType<QList<ObjectInfo>>("QList<ObjectInfo>");
  // qRegisterMetaType<QList<NetAdapter>>("QList<NetAdapter>");
}

AppVariables& AppVariables::instance()
{
  static AppVariables instance;
  return instance;
}
