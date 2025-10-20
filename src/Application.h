#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>

class Application : public QCoreApplication
{
  Q_OBJECT
public:
  Application(int &argc, char **argv);
  ~Application();

  int start();

public slots:
  void exitApp();

private:
  bool initialize();
  bool startHTTP();
  bool startCommandController();
};

#endif // APPLICATION_H
