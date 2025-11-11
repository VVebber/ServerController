#include "NetworkSkan.h"

#include "../Common.h"

#include "Workers/PingWorker.h"
#include "../Models/DeviceInfo.h"
#include "../HTTPServer/Request.h"
#include "../Common/JsonBuilder.h"

#include <QMutex>
#include <QDebug>

NetworkSkan::NetworkSkan()
{
  m_mutex = new QMutex;
}

NetworkSkan::~NetworkSkan()
{
  delete m_mutex;
}

NetworkSkan& NetworkSkan::instance()
{
  static NetworkSkan instance;
  return instance;
}

void NetworkSkan::resetInstance()
{
  qDebug()<<Q_FUNC_INFO;
}

void NetworkSkan::updateAdapterList(QList<NetAdapter> adapters)
{
  for(auto& adapter : adapters)
  {
    if(m_adapters.contains(adapter.name))
    {
      m_adapters[adapter.name] = adapter;
      continue;
    }

    m_adapters.insert(adapter.name, adapter);
  }

  if(m_pingWorker)
  {
    m_pingWorker->isUpdate();
    emit updateAdaptersMap(m_adapters);
  }
}

void NetworkSkan::AddDeviceInfo(DeviceInfo* devise)
{
  qDebug()<<devise->getIpv4()<<":"<<devise->getMac();

  int i = find(m_devices, devise);
  if(i != -1)
  {
    m_devices[i] = devise;
  }
  else
  {
    m_devices.push_back(devise);
  }

  Request req;
  req.type = Request::POST;
  req.url = "http://localhost:3000/device/upsert";
  req.data = JsonBuilder::toJson(devise);

  RequestSender::instance().addRequest(req);
}

void NetworkSkan::run()
{
  qDebug()<<Q_FUNC_INFO;
  startPing();

  Request req;
  req.type = Request::GET;
  req.url = "http://localhost:3000/device/";
  req.callback = [this](const QString& res){
    this->handleDeviceListResponse(res);
  };

  RequestSender::instance().addRequest(req);

  exec();
}

void NetworkSkan::stop()
{
  stopPing();

  quit();
  wait();
}

void NetworkSkan::handleDeviceListResponse(const QString& response)
{
  qDebug()<<response;
}

void NetworkSkan::startPing()
{
  stopPing();

  m_pingWorker = new PingWorker(m_adapters);
  m_pingThread = new QThread;

  m_pingWorker->moveToThread(m_pingThread);

  connect(m_pingThread, &QThread::started, m_pingWorker, &PingWorker::startScan);
  connect(m_pingWorker, &PingWorker::finished, m_pingThread, &QThread::quit);
  connect(this, &NetworkSkan::updateAdaptersMap, m_pingWorker, &PingWorker::update);
  connect(m_pingWorker, &PingWorker::addDeviceInfo, this, &NetworkSkan::AddDeviceInfo);

  m_pingThread->start();
}

void NetworkSkan::stopPing()
{
  if (m_pingThread) {
    m_pingWorker->stop();

    m_pingThread->quit();

    while(m_pingThread->isRunning())

    m_pingThread->wait();



    delete m_pingThread;
    delete m_pingWorker;
  }
}
