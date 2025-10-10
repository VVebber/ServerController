#ifndef COMMON_H
#define COMMON_H

#include <QString>

//!TODO?
// const QString
//!TODO?

const QString ARG_CONSOLE              = "console";

const QString KEY_IF_NAME              = "interface_name";
const QString KEY_IF_INDEX             = "interface_index";
const QString KEY_IF_MAC               = "mac_address";
const QString KEY_CURRENT_IP           = "current_ip";
// const QString KEY_OBJECT_INFO          = "object_info";
const QString KEY_NET_ADAPTERS         = "networkAdapters";
const QString KEY_LOG_OUTPUT_MODE      = "logOutputMode";

const QString UNIX_COMMAND_IP          = "ip";
const QString UNIX_COMMAND_HOSTNAME    = "hostname";

const QString UNIX_FLAG_I              = "-I";
const QString UNIX_ARG_ROUTE           = "route";
const QString UNIX_ARG_LINK            = "link";
const QString UNIX_ARG_SHOW            = "show";

static constexpr unsigned char BROADCAST_MAC[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bool parseMacAddress(const QString& macStr, unsigned char mac[6]);

#endif // COMMON_H
