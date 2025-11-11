#ifndef COMMON_H
#define COMMON_H

#include <QString>

//!TODO?
// const QString
//!TODO?

#define SharedDeviceList QSharedPointer<QList<DeviceInfo>>

const QString ARG_CONSOLE              = "console";

const QString KEY_CURRENT_IP           = "current_ip";
const QString KEY_DEVICE_LIST          = "device_list";
const QString KEY_NET_ADAPTERS         = "networkAdapters";

const QString UNIX_COMMAND_IP          = "ip";
const QString UNIX_COMMAND_HOSTNAME    = "hostname";

const QString UNIX_FLAG_I              = "-I";
const QString UNIX_ARG_ROUTE           = "route";
const QString UNIX_ARG_LINK            = "link";
const QString UNIX_ARG_ADDR            = "addr";
const QString UNIX_ARG_SHOW            = "show";

const QString SCHEME_HTTP              = "http";

const int WINRM_PORT                   = 5985;
const QString WINRM_PATH               = "/wsman";

static constexpr unsigned char BROADCAST_MAC[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bool parseMacAddress(const QString& macStr, unsigned char mac[6]);
int find(QList<class DeviceInfo*> devices, DeviceInfo* device);

#endif // COMMON_H
