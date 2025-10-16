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
  QElapsedTimer m_lastARP;

  static class CheckPing m_CheckPing;

  NetAdapter m_adapter;
  class AppVariables* m_appVariables;
};

#endif // NETWORKSKAN_H


