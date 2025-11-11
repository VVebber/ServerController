#ifndef PINGWORKER_H
#define PINGWORKER_H

#include "IScanWorker.h"

#include <QMap>
#include <atomic>

class PingWorker : public IScanWorker
{
  Q_OBJECT
public:
  explicit PingWorker(const QMap<QString,class NetAdapter> adapter, QObject* parent = nullptr);
  ~PingWorker();

  void startScan() override;

public slots:
  void stop();
  void isUpdate();
  void update(QMap<QString, class NetAdapter> adapters);

signals:
  void addDeviceInfo(class DeviceInfo* device);

private:
  void scan();
  void ping(class NetAdapter adapter);

private:
  class QMap<QString, class NetAdapter> m_adapters;
  std::atomic<bool> m_shouldStop{false};
  std::atomic<bool> m_hasUpdate{false};

  static class CheckPing m_CheckPing;
  static class ARP_Ping m_ARP_ping;

  friend class NetworkSkan;
};

#endif // PINGWORKER_H
