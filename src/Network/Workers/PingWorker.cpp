#include "PingWorker.h"

#include "../../Models/NetAdapter.h"

#include "../../Models/DeviceInfo.h"
#include "../Protocol/ARP/ARP_Ping.h"
#include "../Protocol/ICMP/CheckPing.h"

#include <QTimer>
#include <QDebug>

CheckPing PingWorker::m_CheckPing;
ARP_Ping PingWorker::m_ARP_ping;

PingWorker::PingWorker(const QMap<QString,class NetAdapter> adapters, QObject* parent)
  : IScanWorker(parent), m_adapters(adapters)
{
  qDebug()<<Q_FUNC_INFO;

}

PingWorker::~PingWorker()
{
  qDebug()<<Q_FUNC_INFO;
}

void PingWorker::startScan()
{
  m_shouldStop = false;
  scan();

  QTimer* timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &PingWorker::scan);
  timer->start(60 * 1000);
}

void PingWorker::scan()
{
  if(m_hasUpdate)
    return;

  for (auto& adapter : m_adapters)
  {
    if (m_shouldStop || m_hasUpdate)
      break;

    if (!adapter.isAtive)
      continue;

    ping(adapter);

  }

  if (m_shouldStop)
    emit finished();
}

void PingWorker::stop()
{
  qDebug() << "Stop requested!";
  m_shouldStop = true;
}

void PingWorker::isUpdate()
{
  m_hasUpdate = true;
}

void PingWorker::update(QMap<QString, NetAdapter> adapters)
{
  m_adapters = adapters;
  m_hasUpdate = false;
}

void PingWorker::ping(NetAdapter adapter)
{
  int count = adapter.ipv4.count("%");
  int max3 = (count >= 3 ? 255 : 0);
  int max2 = (count >= 2 ? 255 : 0);
  int max1 = (count >= 1 ? 100 : 0);
  //TODO? move this to another thread
  for(int i3 = 0; i3 <= max3 && !m_shouldStop && !m_hasUpdate; i3++)
  {
    for(int i2 = 0; i2 <= max2 && !m_shouldStop && !m_hasUpdate; i2++)
    {
      for(int i1 = 0; i1 <= max1 && !m_shouldStop && !m_hasUpdate; i1++)
      {
        QString ip = adapter.ipv4;

        if (count >= 1) ip = ip.arg(i1);
        if (count >= 2) ip = ip.arg(i2);
        if (count >= 3) ip = ip.arg(i3);

        std::string ipStr = ip.toStdString();

        PingRes pingRes = m_CheckPing.process(ipStr.c_str());
        ArpPingRes arpRes = m_ARP_ping.process(ipStr.c_str(), adapter);


        if(!QString(arpRes.ip).isEmpty() ||
           !QString(pingRes.ip).isEmpty())
        {
          DeviceInfo* device = new DeviceInfo();

          device->setIpv4(ip);
          device->setMac(QString(arpRes.mac));
          device->setAdapterName(adapter.name);

          emit addDeviceInfo(device);
        }

        if (m_shouldStop)
            return;
      }
    }
  }
}
