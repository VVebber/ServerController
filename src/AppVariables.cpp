#include "AppVariables.h"
// #include "Tasks/ObjectInfo.h"
// #include "Models/NetAdapter.h"

// #include <QMetaType>

// Q_DECLARE_METATYPE(QList<ObjectInfo>)

AppVariables::AppVariables()
{
  qDebug()<<Q_FUNC_INFO;
}

AppVariables::~AppVariables()
{
  qDebug()<<Q_FUNC_INFO;
}

AppVariables& AppVariables::instance()
{
  static AppVariables instance;
  return instance;
}

void AppVariables::resetInstance()
{

}
