#include "EthtoolUtil.h"

static int Pos(DynSet<AnsiString>& cmds, AnsiString str) {
  for(int i=0;i<cmds.Size();i++)
    if(cmds[i].Pos(str) != 0) {
      return i;
    }
  return -1;
}

bool EthtoolUtil::isPlugIn(const AnsiString& iface) {
  if(!ShellUtil::CmdExist("ethtool"))
    throw Exception("ethtool not found!");
  DynSet<AnsiString> res = ShellUtil::exec("sudo ethtool " + iface);
  for(int i=0;i<res.Size();i++) {
    Logger::log("[EthtoolUtil]["+AnsiString(i)+"]"+res[i]);
  }
  return Pos(res, "Link detected: yes") != -1;
}
