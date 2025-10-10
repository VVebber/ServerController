#include "Application.h"
#include "Logs/Log.h"
#include "AgrParser.h"

#include <iostream>
int main(int argc, char *argv[])
{
  AgrParser argParser(argc, argv);
  argParser.parse();

  initLog("ServerController");

  Application a(argc, argv);
  a.start();

  finishgLog(1);
  return 0;
}
