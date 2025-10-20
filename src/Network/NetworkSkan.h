#ifndef NETWORKSKAN_H
#define NETWORKSKAN_H

#include <QElapsedTimer>
#include "../Models/NetAdapter.h"

class NetworkSkan
{
public:
  NetworkSkan(NetAdapter adapter);
  ~NetworkSkan();

  void start();
  void stop();

  void updateAdapter(NetAdapter adapter);

private:
  void ping();

private:
  class QMutex *m_mutex;
  class QTimer *m_timer;

  QElapsedTimer m_lastPing;

  static class CheckPing m_CheckPing;
  static class ARP_Ping m_ARP_ping;

  NetAdapter m_adapter;
  class AppVariables* m_appVariables;
};

#endif // NETWORKSKAN_H


