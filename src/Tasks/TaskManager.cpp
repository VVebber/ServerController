#include "TaskManager.h"

#include "ConsoleCommand.h"

#include "../Common.h"
#include "../AppVariables.h"
#include "../Models/NetAdapter.h"

#include <QThread>
#include <QDebug>
#include <QRegularExpression>


TaskManager *TaskManager::m_taskManager = nullptr;

TaskManager* TaskManager::instance()
{
  if(m_taskManager == nullptr)
  {
    m_taskManager = new TaskManager;

    QThread* taskThread = new QThread;

    m_taskManager->moveToThread(taskThread);

    connect(taskThread, &QThread::started, m_taskManager, &TaskManager::process);
    connect(m_taskManager, &TaskManager::finished, taskThread, &QThread::quit);

    taskThread->start();
  }

  return m_taskManager;
}

TaskManager::TaskManager()
{
  qDebug()<<Q_FUNC_INFO;
  m_appVariables = &AppVariables::instance();

  m_idTimer = 0;
}

void TaskManager::resetInstance()
{
  qDebug()<<Q_FUNC_INFO;

  if(m_taskManager != nullptr)
  {
    QThread* taskThread = m_taskManager->thread();


    delete taskThread;
    delete m_taskManager;
  }
}

void TaskManager::process()
{
  qDebug()<<Q_FUNC_INFO;
  getCurrentIp();


  // 6 * 60 * 60 * 1000 6 часов
  m_idTimer = startTimer(6 * 60 * 60 * 1000);
  timerEvent(nullptr);
}

void TaskManager::timerEvent(QTimerEvent* event)
{
  qDebug()<<Q_FUNC_INFO;
  loadPrimaryInterfaceInfo();
  checkInterfaces();

  QVariant v = AppVariables::instance().get(KEY_NET_ADAPTERS);
  QList<NetAdapter> adapters = v.value<QList<NetAdapter>>();

  for(auto& adapter : adapters)
  {
    qDebug()<<"name: "<<adapter.name;
    qDebug()<<"mac: "<<adapter.mac;
    qDebug()<<"active: "<<adapter.isAtive;
  }
}

bool TaskManager::getCurrentIp()
{
  QStringList args = {UNIX_FLAG_I};
  ConsoleCommand getIp;
  if(getIp.runCommand(UNIX_COMMAND_HOSTNAME, args))
  {
    QRegularExpression ipRegex(R"((\d{1,3}\.){3}\d{1,3})");
    QRegularExpressionMatch match = ipRegex.match(getIp.m_standartOut.trimmed());
    if(match.hasMatch())
    {
      QString ip = match.captured(0);
      qDebug() << "Current machine IP: "<< ip;
      m_appVariables->add(KEY_CURRENT_IP, ip);
      return true;
    }
  }

  qWarning() << "Не удалось получить текущий IP";
  return false;
}

void TaskManager::loadPrimaryInterfaceInfo()
{
  qDebug()<<Q_FUNC_INFO;

  QStringList args = {UNIX_ARG_LINK};
  ConsoleCommand ipShow;
  if(ipShow.runCommand(UNIX_COMMAND_IP, args))
  {

    QList<NetAdapter> adapterList;

    if(m_appVariables->contains(KEY_NET_ADAPTERS))
    {
      QVariant v = m_appVariables->get(KEY_NET_ADAPTERS);
      adapterList = v.value<QList<NetAdapter>>();
    }

    QRegularExpression macRegex(R"(link/\w+\s+([0-9a-fA-F]{2}(?::[0-9a-fA-F]{2}){5}))");
    QRegularExpression ifInterfaceRegex(R"(\d+: ([^:]+))");

    QRegularExpressionMatchIterator macMatch = macRegex.globalMatch(ipShow.m_standartOut);
    QRegularExpressionMatchIterator ifaceMatch = ifInterfaceRegex.globalMatch(ipShow.m_standartOut);

    while (ifaceMatch.hasNext() && macMatch.hasNext())
    {
      QString name = ifaceMatch.next().captured(1);
      QString mac = macMatch.next().captured(1);

      NetAdapter adapter;
      adapter.name = name;
      adapter.mac = mac;

      bool isFind = false;
      for(auto& adapter : adapterList)
      {
        if(adapter.mac == mac)
        {
          isFind = true;
        }
      }

      if(!isFind && name != "lo")
        adapterList.append(adapter);
    }
    m_appVariables->add(KEY_NET_ADAPTERS, QVariant::fromValue(adapterList));
  }
}

void TaskManager::checkInterfaces()
{
  qDebug()<<Q_FUNC_INFO;

  QStringList args = {UNIX_ARG_ROUTE};
  ConsoleCommand getStatusInterface;
  if(getStatusInterface.runCommand(UNIX_COMMAND_IP, args))
  {
    QStringList routeLines = getStatusInterface.m_standartOut.split("\n", Qt::SkipEmptyParts);
    routeLines.pop_front();

    QVariant v = m_appVariables->get(KEY_NET_ADAPTERS);
    QList<NetAdapter> adapters = v.value<QList<NetAdapter>>();

    for (NetAdapter &adapter : adapters)
    {
      adapter.isAtive = false;
    }

    for (const QString &line : routeLines)
    {
      QStringList parts = line.split(' ', Qt::SkipEmptyParts);


      for (NetAdapter &adapter : adapters)
      {
        if (parts.contains(adapter.name))
        {
          if(!parts.contains("linkdown"))
          {
            adapter.isAtive = true;
            continue;
          }
        }
      }
    }
    m_appVariables->add(KEY_NET_ADAPTERS, QVariant::fromValue(adapters));
  }
}

