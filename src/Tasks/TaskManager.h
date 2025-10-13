#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QMap>

class TaskManager : public QObject
{
  Q_OBJECT

signals:
  void finished();

private:
  TaskManager();
  ~TaskManager();
  void fetchInterfaceInfo();
  void addAdapter(QList<class NetAdapter>& adapterList, NetAdapter& adapter);

  bool getCurrentIp();

private slots:
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
