#include "Log.h"
#include "../AppVariables.h"
#include "../Common.h"
// #include <stdio.h>
// #include <stdlib.h>

#include <iostream>

#ifdef Q_OS_UNIX
#include <signal.h>
#include <syslog.h>
#endif

#if defined(Q_OS_WIN)
static
#elif defined(Q_OS_LINUX)

static std::string appName;
#endif

static std::string outputMode;

void LogMessageOutpot(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
  QString message = "";

  int protety = LOG_NOTICE;

  switch (type)
  {
    case QtDebugMsg:
      message.append(" [DEBUG   ");
      protety = LOG_DEBUG;
      break;
    case QtInfoMsg:
      message.append(" [INFO    ");
      protety = LOG_INFO;
      break;
    case QtCriticalMsg:
      message.append(" [ERROR   ");
      protety = LOG_ERR;
      break;
    case QtFatalMsg:
      message.append(" [FATAL   ");
      protety = LOG_CRIT;
      break;
    case QtWarningMsg:
      message.append(" [WARNING ");
      protety = LOG_WARNING;
      break;
  }

  message.append(context.category);
  message.append("]");
  message.append("\t" +msg);

  if(::outputMode == ARG_CONSOLE)
  {
    std::cout<<message.toStdString()<<std::endl;
  }
  else
  {
    openlog(::appName.c_str(), LOG_PID, LOG_USER);
    syslog(protety, "%s", message.toStdString().c_str());
    closelog();
  }
}

void setOutputMode(const std::string& mode)
{
  ::outputMode = mode;
}

bool initLog(const std::string& appName)
{
  ::appName = appName;
#ifdef Q_OS_LINUX
  signal(SIGABRT, finishgLog);

  openlog(::appName.c_str(), LOG_PID, LOG_USER);
  syslog(LOG_INFO, "--- Controller started ---");
  closelog();
#endif

  qInstallMessageHandler(LogMessageOutpot);

  return true;
}

void finishgLog(int signal)
{
#ifdef Q_OS_LINUX
  openlog(::appName.c_str(), LOG_PID, LOG_USER);
  syslog(LOG_INFO, "--- Controller finished ---");
  closelog();

  exit(signal);
#endif
}
