#ifndef IFCONFIG_UTILS
#define IFCONFIG_UTILS

#include "ShellUtil.h"

class IfconfigUtil {
  public:
    static AnsiString getEthName();
    static AnsiString getLteName();
    static AnsiString getWifiName();
    static AnsiString getEthIp();
    static AnsiString getLteIp();
    static void setIp(const AnsiString&, const AnsiString&);
    static void setNetmask(const AnsiString&, const AnsiString&);
};

#endif