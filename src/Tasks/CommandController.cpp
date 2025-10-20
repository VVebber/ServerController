#include "CommandController.h"

#include <QString>
#include <QTextStream>
#include <QSocketNotifier>
#include <QDebug>

CommandController* CommandController::instance()
{
  static CommandController instance;
  return &instance;
}

bool CommandController::start()
{
  bool  isGood = true;
  initICommands();

  // isGood = connect(m_readDataSok, &QSocketNotifier::activated,
  //                  [this](int){ data(); });

  return isGood;
}

void CommandController::initICommands()
{
  // ....
}

void CommandController::resetInstance()
{

}

// void CommandController::data()
// {
//   qDebug()<<Q_FUNC_INFO;
//   QString str;
//   static QTextStream in(stdin);
//   static QTextStream out(stdout);

//   out <<"> ";
//   out.flush();

//   if(in.readLineInto(&str))
//   {
//     // ICommand.add(str);
//   }
// }

CommandController::CommandController()
{
  m_readDataSok = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read);
}


CommandController::~CommandController()
{

}
