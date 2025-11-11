#include "AppVariables.h"

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

void AppVariables::setCurrentIp(const QString& ip)
{
  m_currentIp = ip;
}

QString AppVariables::getCurrentIp() const{
  return m_currentIp;
}
