#include "TaskManager.h"

#include "ConsoleCommand.h"

#include "../Common.h"
#include "../AppVariables.h"
#include "../Models/NetAdapter.h"
#include "../Network/NetworkSkan.h"

#include <QDebug>
#include <QThread>
#include <QCoreApplication>
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
    connect(taskThread, &QThread::finished, m_taskManager, &TaskManager::quit);

    taskThread->start();
  }

  return m_taskManager;
}

void TaskManager::resetInstance()
{
  qDebug()<<Q_FUNC_INFO;

  if(m_taskManager != nullptr)
  {
    QThread* taskThread = m_taskManager->thread();

    taskThread->quit();
    taskThread->wait();

    // while(taskThread->isRunning())
    // {
    //   QThread::msleep(1);
    //   QCoreApplication::instance()->processEvents(QEventLoop::AllEvents, 100);
    // }

    delete taskThread;
    delete m_taskManager;
  }
}

TaskManager::TaskManager()
{
  qDebug()<<Q_FUNC_INFO;
  m_appVariables = &AppVariables::instance();
}

TaskManager::~TaskManager()
{
  qDebug()<<Q_FUNC_INFO;


}

void TaskManager::quit()
{
  qDebug()<<Q_FUNC_INFO;

  if (m_idTimer) {
    killTimer(m_idTimer);
    m_idTimer = 0;
  }

  for(auto& skan : m_networkSkanList)
  {
    skan->stop();
    delete skan;
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
  fetchInterfaceInfo();

  QVariant v = AppVariables::instance().get(KEY_NET_ADAPTERS);
  QList<NetAdapter> adapters = v.value<QList<NetAdapter>>();

  for(auto& adapter : adapters)
  {
    if(m_networkSkanList.contains(adapter.name))
    {
      m_networkSkanList[adapter.name]->updateAdapter(adapter);
      continue;
    }

    NetworkSkan* scan = new NetworkSkan(adapter);

    m_networkSkanList.insert(adapter.name, scan);
    scan->start();
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

void TaskManager::fetchInterfaceInfo()
{
  qDebug()<<Q_FUNC_INFO;

  QStringList args = {UNIX_ARG_ADDR};
  ConsoleCommand ipShow;

  if(ipShow.runCommand(UNIX_COMMAND_IP, args))
  {
    QStringList lines =ipShow.m_standartOut.split("\n", Qt::SkipEmptyParts);

    QList<NetAdapter> adapterList;
    NetAdapter currentAdapter;

    if(m_appVariables->contains(KEY_NET_ADAPTERS))
    {
      QVariant v = m_appVariables->get(KEY_NET_ADAPTERS);
      adapterList = v.value<QList<NetAdapter>>();
    }

    QRegularExpression macRegex(R"(link/\w+\s+([0-9a-fA-F]{2}(?::[0-9a-fA-F]{2}){5}))");
    QRegularExpression ifInterfaceRegex(R"(\d+: ([^:]+))");
    QRegularExpression ipWithMaskRegex(R"(inet\s+(\d{1,3}(?:\.\d{1,3}){3}/\d{1,2}))");
    QRegularExpression flagsRegex(R"(<([^>]+)>)");

    for(const QString& line: lines)
    {
      QRegularExpressionMatch ifaceM = ifInterfaceRegex.match(line);
      if(ifaceM.hasMatch())
      {
        addAdapter(adapterList, currentAdapter);
        currentAdapter.name = ifaceM.captured(1);
        currentAdapter.ifIndex = ifaceM.captured(0).section(":", 0,0).toInt();
      }

      QRegularExpressionMatch flagsM = flagsRegex.match(line);
      if(flagsM.hasMatch())
      {
        QString flags = flagsM.captured(1);
        if (!flags.contains("NO-CARRIER") && (flags.contains("UP") || flags.contains("LOWER_UP")))
        {
          currentAdapter.isAtive = true;
        }
        continue;
      }

      QRegularExpressionMatch macM = macRegex.match(line);
      if(macM.hasMatch())
      {
        currentAdapter.mac = macM.captured(1);
        continue;
      }

      QRegularExpressionMatch ipM = ipWithMaskRegex.match(line);
      if(ipM.hasMatch())
      {
        QString ipv4 = ipM.captured(1);
        currentAdapter.ipv4 = ipv4.section("/", 0, 0);
        currentAdapter.setIp(ipv4.section("/", 1, 1));
        continue;
      }
    }
    addAdapter(adapterList, currentAdapter);

    m_appVariables->add(KEY_NET_ADAPTERS, QVariant::fromValue(adapterList));
  }
}

void TaskManager::addAdapter(QList<NetAdapter>& adapterList, NetAdapter& adapter)
{
  if(!adapter.name.isEmpty() && adapter.name != "lo")
  {
    int isFind = -1;
    for(int i = 0; i < adapterList.count(); i++)
    {
      if(adapterList[i].name == adapter.name)
      {
        isFind = i;
        break;
      }
    }

    if(isFind == -1)
    {
      adapterList.append(adapter);
    }
    else
    {
      adapterList[isFind] = adapter;
    }
    adapter = NetAdapter();
  }
}
