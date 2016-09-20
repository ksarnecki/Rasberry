#include "RouteUtil.h"

void RouteUtil::setDefault(const AnsiString& iface) {
  Logger::log("[RouteUtil][setDefault] " + iface);
  bool change = true;
  DynSet<AnsiString> res = ShellUtil::exec("ip route | grep default");
  for(int i=0;i<res.Size();i++) {
    AnsiString& rule = res[i];
    if(rule.Pos(iface) > 0) {
      change = false;
      continue;
    } 
    ShellUtil::exec("sudo ip route del " + rule);
  }
  if(!change)
    return;
  for(int i=0;i<res.Size();i++) {
    if(res[i].Pos(iface) >  0) {
      ShellUtil::exec("sudo ip route add " + res[i]);
      return;
    }
  }
}