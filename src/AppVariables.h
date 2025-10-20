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
  static void resetInstance();
  void add(const QString &key, const QVariant &value) {
    QMutexLocker locker(&m_mutex);
    m_variables.insert(key, value);
  }

  QVariant get(const QString &key, const QVariant &defaultValue = QVariant()) const {
    QMutexLocker locker(&m_mutex);
    return m_variables.value(key, defaultValue);
  }

  bool contains(const QString &key) const {
    QMutexLocker locker(&m_mutex);
    return m_variables.contains(key);
  }

  void remove(const QString &key) {
    QMutexLocker locker(&m_mutex);
    m_variables.remove(key);
  }

private:
  AppVariables();
  ~AppVariables();
  AppVariables(const AppVariables&) = delete;
  AppVariables& operator=(const AppVariables&) = delete;

private:
  QMultiMap<QString, QVariant> m_variables;
  mutable QMutex m_mutex;
};

#endif // APPVARIABLES_H
