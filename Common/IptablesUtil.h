#ifndef IPTABLES_UTIL
#define IPTABLES_UTIL

#include "ShellUtil.h"
#include "Logger.h"

class IptablesUtil {
  private:
    static void update(const AnsiString&);
    static AnsiString genDefaultString(const AnsiString&, const DynSet<AnsiString>&);
  public:
    static void setDefault(const AnsiString&, const DynSet<AnsiString>&);
};

#endif
