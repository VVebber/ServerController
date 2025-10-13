#ifndef NETWORKSKAN_H
#define NETWORKSKAN_H

#include "../Models/NetAdapter.h"

class NetworkSkan
{
public:
  NetworkSkan(NetAdapter adapter);

  void start();
  void stop();

  void updateAdapter(NetAdapter adapter);

private:
  class ICMP* m_ICMP;
  class ARP* m_ARP;

  class QTimer* m_ICMP_Timer;
  class QTimer* m_ARP_Timer;

  class QMutex *m_mutex;

  NetAdapter m_adapter;
};

#endif // NETWORKSKAN_H


