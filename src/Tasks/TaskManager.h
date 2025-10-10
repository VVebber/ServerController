#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>

class TaskManager : public QObject
{
  Q_OBJECT

signals:
  void finished();

private:
  TaskManager();
  void checkInterfaces();
  void loadPrimaryInterfaceInfo();

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
  bool isFinished = false;

  class AppVariables* m_appVariables;
};

#endif // TASKMANAGER_H
