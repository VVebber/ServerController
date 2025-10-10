#ifndef NETWORKSKAN_H
#define NETWORKSKAN_H

class NetworkSkan
{
public:
  NetworkSkan();

  void start();
  void stop();

private:
  class ICMP* m_ICMP;
  class ARP* m_ARP;

  class QTimer* m_ICMP_Timer;
  class QTimer* m_ARP_Timer;

  class QMutex *m_mutex;
};

#endif // NETWORKSKAN_H


