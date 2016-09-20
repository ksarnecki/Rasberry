#ifndef DHCP_UTIL
#define DHCP_UTIL

#include "IfconfigUtil.h"
#include "ShellUtil.h"
#include "ShellUtil.h"

class DhcpUtil {
  public:
    static void setConfig();
    static void startServer();
    static void stopServer();
    static bool dhcpSeverDetected();
    static AnsiString getDhcpServerAddress();
};

#endif