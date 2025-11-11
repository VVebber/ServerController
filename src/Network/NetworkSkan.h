#ifndef NETWORKSKAN_H
#define NETWORKSKAN_H

#include "../Models/NetAdapter.h"
#include "../Models/DeviceInfo.h"

#include <QMap>
#include <QThread>

class NetworkSkan : public QThread
{
  Q_OBJECT
public:
  static NetworkSkan& instance();
  void resetInstance();

public slots:
  void run() override;
  void stop();
  void updateAdapterList(QList<NetAdapter> adapter);
  void AddDeviceInfo(DeviceInfo* device);

signals:
  void updateAdaptersMap(QMap<QString, NetAdapter> adapters);

private:
  NetworkSkan();
  ~NetworkSkan();

  void startPing();
  void stopPing();

  void handleDeviceListResponse(const QString& response);

private:

private:
  class QMutex *m_mutex;

  QThread* m_pingThread;
  class PingWorker* m_pingWorker;

  QMap<QString, NetAdapter> m_adapters;
  QList<DeviceInfo*> m_devices;
};

#endif // NETWORKSKAN_H

// SSHWorker / WinRMWorker — отдельные потоки при необходимости.
// NetFlowWorker — отдельный поток для обработки потоковой информации.
