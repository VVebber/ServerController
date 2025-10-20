#include "Application.h"
#include "Logs/Log.h"
#include "AgrParser.h"

#include <iostream>

#ifdef Q_OS_LINUX
  #include <signal.h>
#endif

void signal(int signal)
{
  QCoreApplication::instance()->quit();
}

int main(int argc, char *argv[])
{
  AgrParser argParser(argc, argv);
  argParser.parse();

  initLog("ServerController");

#ifdef Q_OS_LINUX
  signal(SIGINT, signal);
  signal(SIGTERM, signal);
#endif

  Application a(argc, argv);
  a.start();

  a.exitApp();

  finishgLog(0);
}
