#include "NetworkSkan.h"

// #include "./ObjectInfo.h"
#include "../Common.h"
#include "../AppVariables.h"
#include "../Network/Protocol/ICMP/ICMP.h"
#include "../Network/Protocol/ARP/ARP.h"

#include <QTimer>
#include <QMutex>



NetworkSkan::NetworkSkan()
{
  m_ICMP = new ICMP;
  m_ICMP_Timer = new QTimer;

  m_ARP = new ARP;
  m_ARP_Timer = new QTimer;

  m_mutex = new QMutex;
}

void NetworkSkan::start()
{
  if (m_ICMP_Timer != nullptr) {
    QObject::connect(m_ICMP_Timer, &QTimer::timeout, [this]() {
      QMutexLocker locker(m_mutex);
      m_ICMP->process();
    });

    m_ICMP_Timer->start(1000);
  }

  if(m_ARP_Timer != nullptr)
  {
    QObject::connect(m_ARP_Timer, &QTimer::timeout, [this]() {
      QMutexLocker locker(m_mutex);
      // QVariant var = AppVariables::instance().get(KEY_OBJECT_INFO);
      // QList<ObjectInfo>* objectList = var.value<QList<ObjectInfo>*>();
      // for(int i = 0; i < objectList->count(); i++)
      // {
      //   // m_ARP->process((*objectList)[i]);
      // }
    });

    m_ARP_Timer->start(1000);
  }

  m_ICMP->process();
  // QVariant var = AppVariables::instance().get(KEY_OBJECT_INFO);
  // QList<ObjectInfo>* objectList = var.value<QList<ObjectInfo>*>();
  // for(int i = 0; i < objectList->count(); i++)
  // {
    // m_ARP->process((*objectList)[i]);
  // }
}

void NetworkSkan::stop()
{
  if (m_ICMP_Timer) {
    m_ICMP_Timer->stop();
    m_ICMP_Timer->deleteLater();
    m_ICMP_Timer = nullptr;
  }

  if (m_ARP_Timer) {
    m_ARP_Timer->stop();
    m_ARP_Timer->deleteLater();
    m_ARP_Timer = nullptr;
  }
}
