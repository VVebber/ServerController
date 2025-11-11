#include "WinRM.h"

#include "../../../Common.h"
#include "../../../Models/DeviceInfo.h"
#include "../../../HTTPServer/Request.h"

#include <openwsman/cpp/OpenWsmanClient.h>
#include <openwsman/cpp/WsmanOptions.h>
#include <u/libu.h>

using namespace WsmanClientNamespace;

WinRM::WinRM(){}

void WinRM::setDevice(DeviceInfo* device)
{
  if(device || device == m_device)
    return;

  m_device = device;

  if(!m_client)
  {
    m_client = new OpenWsmanClient(
                 device->m_ipv4.toStdString(),
                 WINRM_PORT,
                 WINRM_PATH.toStdString(),
                 SCHEME_HTTP.toStdString(),
                 "basic",
                 device->m_userName.toStdString(),
                 device->m_password.toStdString()
                 );
  }
  else
  {
    delete m_client;
    m_client = new OpenWsmanClient(
        device->m_ipv4.toStdString(),
        WINRM_PORT,
        WINRM_PATH.toStdString(),
        SCHEME_HTTP.toStdString(),
        "basic",
        device->m_userName.toStdString(),
        device->m_password.toStdString()
    );
  }
}

void WinRM::process(TypeResurs typeResurs)
{
  return;
  WsmanOptions options;

  QString resurceUrl = urlResurs(typeResurs);

  vector<std::string> vec;

  m_client->Enumerate(resurceUrl.toStdString(), vec, options);
}
