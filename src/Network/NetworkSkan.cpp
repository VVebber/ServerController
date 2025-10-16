#include "NetworkSkan.h"

#include "../Common.h"
#include "../AppVariables.h"
#include "../Network/Protocol/ICMP/CheckPing.h"
#include "../Network/Protocol/ARP/ARP.h"

#include "../Models/DeviceInfo.h"

#include <QMutex>
#include <QTimer>
#include <QElapsedTimer>
#include <QSharedPointer>

CheckPing NetworkSkan::m_CheckPing;


NetworkSkan::NetworkSkan(NetAdapter adapter): m_adapter(adapter)
{
  qDebug()<<Q_FUNC_INFO;
  m_appVariables = &AppVariables::instance();

  m_timer = new QTimer;
  m_mutex = new QMutex;
}

NetworkSkan::~NetworkSkan()
{
  delete m_timer;
  delete m_mutex;
}

void NetworkSkan::updateAdapter(NetAdapter adapter)
{
  m_adapter = adapter;
}


void NetworkSkan::start()
{
  qDebug()<<m_adapter.name<<": "<<Q_FUNC_INFO;

  bool iFind = true;

  m_timer->setInterval(1 * 1000);
  m_lastPing.start();


  QObject::connect(m_timer, &QTimer::timeout, [=](){

    if(m_lastPing.hasExpired(1 * 1 * 1000))
    {
      ping();
      m_lastPing.restart();
    }

    if(m_lastARP.hasExpired(2 * 60 * 1000))
    {
      // qDebug()<<"Ping";
      m_lastARP.elapsed();
    }
  });
  m_timer->start();
}

void NetworkSkan::ping()
{
  qDebug()<<Q_FUNC_INFO;

  SharedDeviceList DeviseList;

  if(m_appVariables->contains(KEY_DEVICE_LIST))
  {
    QVariant v = m_appVariables->get(KEY_DEVICE_LIST);
    DeviseList = v.value<SharedDeviceList>();
  }

  int count = m_adapter.ipv4.count("%");
  int max3 = (count >= 3 ? 255 : 0);
  int max2 = (count >= 2 ? 255 : 0);
  int max1 = (count >= 1 ? 255 : 0);


  return;
  for(int i3 = 0; i3 <= max2; i3++)
  {
    for(int i2 = 0; i2 <= max2; i2++)
    {
      for(int i1 = 0; i1 <= max1; i1++)
      {
        m_CheckPing.process(m_adapter.ipv4.arg(i1).toStdString().c_str());
      }
    }
  }
  //Тут будет ping по Adapter и добавление в SharedDeviceList;
}

void NetworkSkan::stop()
{
  m_timer->stop();
  // QObject::disconnect(m_timer, &QTimer::timeout);
}
