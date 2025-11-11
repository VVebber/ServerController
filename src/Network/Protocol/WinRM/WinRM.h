#ifndef WINRM_H
#define WINRM_H

#include "TypeResure.h"

#include <QObject>

class DeviceInfo;
namespace WsmanClientNamespace {
  class OpenWsmanClient;
}

class WinRM : public QObject
{
  Q_OBJECT
public:
  WinRM();

  void setDevice(DeviceInfo* device);
  void process(TypeResurs base);
private:
  DeviceInfo* m_device = nullptr;

  WsmanClientNamespace::OpenWsmanClient* m_client;
};

#endif // WINRM_H

// Классы
//  OpenWsmanClient         точка входа с запросами
//  WsmanClient             тоже самое что OpenWsmanClient, только низкоуровневое
//  WsmanOptions            опция зпроса оперусов/операций и тд
//  WsmanSelectors          ....
//  WsmanFilter             фильтр
//  WsmanException          для исключений
//  WsmanClientTransport    работа с http/https
