#ifndef WINRMWORKER_H
#define WINRMWORKER_H

#include "IScanWorker.h"

class WinMR;

class WinRMWorker : public IScanWorker
{
  Q_OBJECT

  void startScan() override;

public:
  WinRMWorker();

private:
  // WinRM m_winRM;
};

#endif // WINRMWORKER_H
