#include "Application.h"

#include "Tasks/TaskManager.h"

#include <QDebug>

// #include "Tasks/ObjectInfo.h"

Application::Application(int &argc, char **argv) :
  QCoreApplication(argc, argv)
{
  // QList<ObjectInfo>* objectList = new QList<ObjectInfo>;

  // AppVariables::instance().add(KEY_OBJECT_INFO, QVariant::fromValue(objectList));
}

int Application::start()
{
  qDebug()<<Q_FUNC_INFO;

  if(!initialize())
    return 1;

  TaskManager::instance();

  return exec();
}
bool Application::startHTTP()
{
  return false;
}

void Application::exitApp()
{
  TaskManager::resetInstance();
}


bool Application::initialize()
{
  qDebug()<<Q_FUNC_INFO;

  if(!startHTTP())
  {
    qWarning() <<"Не удалось запустить прослушивание http";
  }

  return true;
}
