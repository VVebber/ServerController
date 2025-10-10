#include "ConsoleCommand.h"

#include <QProcess>
#include <QDebug>

bool ConsoleCommand::runCommand(const QString& command, const QStringList& args)
{
  QProcess proccess;
  proccess.start(command, args);
  proccess.waitForFinished();

  m_standartOut = proccess.readAllStandardOutput();
  m_errorOut = proccess.readAllStandardError();

  if(m_standartOut.isEmpty())
  {
    qWarning()<<m_errorOut;
    return false;
  }

  return true;
}
