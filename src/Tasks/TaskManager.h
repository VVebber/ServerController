#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QMap>

class TaskManager : public QObject
{
  Q_OBJECT
private:
  TaskManager();
  ~TaskManager();

  QList<class NetAdapter> fetchInterfaceInfo();
  void addAdapter(QList<class NetAdapter>& adapterList, NetAdapter& adapter);

  bool getCurrentIp();

signals:
  void updateAdapterList(QList<NetAdapter> adapter);
  void finished();

private slots:
  void quit();
  void process();
  void timerEvent(QTimerEvent* event) override;

public:
  static TaskManager* instance();
  static void resetInstance();

private:
  static TaskManager* m_taskManager;

  int m_idTimer;
  // bool isFinished = false;

  class AppVariables* m_appVariables;
  QMap<QString, class NetworkSkan*> m_networkSkanList;
};

#endif // TASKMANAGER_H
