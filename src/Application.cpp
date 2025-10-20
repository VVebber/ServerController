#include "Application.h"

#include "Tasks/TaskManager.h"
// #include "Tasks/CommandController.h"

#include <QDebug>

Application::Application(int &argc, char **argv) :
  QCoreApplication(argc, argv)
{

}

Application::~Application()
{
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

bool Application::startCommandController()
{
  // if(!CommandController::instance()->start())
  // {
  //   return false;
  // }

  return true;
}

bool Application::initialize()
{
  qDebug()<<Q_FUNC_INFO;

  // if(!startCommandController())
  // {
  //   return false;
  // }

  if(!startHTTP())
  {
    qWarning() <<"Не удалось запустить прослушивание http";
  }



  return true;
}
