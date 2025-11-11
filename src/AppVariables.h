// AppVariables.h
#ifndef APPVARIABLES_H
#define APPVARIABLES_H

#include <QString>
#include <QVariant>
#include <QMultiMap>
#include <QMutex>
#include <QMutexLocker>

class AppVariables
{

public:
  static AppVariables& instance();

  void setCurrentIp(const QString& ip);
  QString getCurrentIp() const;

private:
  AppVariables();
  ~AppVariables();
  AppVariables(const AppVariables&) = delete;
  AppVariables& operator=(const AppVariables&) = delete;

private:
  QString m_currentIp;
};

#endif // APPVARIABLES_H
