#ifndef CONSOLECOMMAND_H
#define CONSOLECOMMAND_H

#include <QString>

class ConsoleCommand
{
public:
  ConsoleCommand() = default;

  bool runCommand(const QString& command, const QStringList& args);

  QString m_standartOut;
  QString m_errorOut;
};

#endif // CONSOLECOMMAND_H
