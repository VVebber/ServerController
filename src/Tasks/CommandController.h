#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>

class CommandController : public QObject
{
  Q_OBJECT
public:
  static CommandController* instance();
  static void resetInstance();

  // void Attach()
  bool start();
private:
  void initICommands();
  // void data();

  CommandController();
  ~CommandController();

private:
  class QSocketNotifier* m_readDataSok;
  // QStringList listCommand
};

#endif // COMMANDCONTROLLER_H
