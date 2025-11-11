#include "Application.h"

#include "Tasks/TaskManager.h"
// #include "Tasks/CommandController.h"
#include "HTTPServer/NetWorker.h"

#include <QDebug>
#include <QThread>

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
  m_netWorker = new NetWorker();
  QThread* thread = new QThread();

  m_netWorker->moveToThread(thread);
  thread->start();

  connect(&RequestSender::instance(), &RequestSender::sendRequest,
          m_netWorker, &NetWorker::addRequest,
          Qt::QueuedConnection);

  thread->start();

  return true;
}

void Application::exitApp()
{
  TaskManager::resetInstance();

  QThread* netThread = m_netWorker->thread();

  netThread->quit();
  netThread->wait();

  delete netThread;
  delete m_netWorker;
}

// bool Application::startCommandController()
// {
  // if(!CommandController::instance()->start())
  // {
  //   return false;
  // }

  // return true;
// }

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
