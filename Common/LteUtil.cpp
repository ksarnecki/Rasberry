#include "LteUtil.h"

void LteUtil::mount() {
  Logger::log("[LteUtil][mount]");
  if(!ShellUtil::CmdExist("lsusb"))
    throw Exception("lsusb not found!");
  if(!ShellUtil::CmdExist("sg_raw"))
    throw Exception("sg_raw not found!");
  DynSet<AnsiString> res = ShellUtil::exec("lsusb | grep Huawei | grep 1f01");
  if(res.Size()>0) {
    ShellUtil::exec("sg_raw /dev/sr0 11 06 20 00 00 00 00 00 01 00");
    ShellUtil::exec("sg_raw /dev/sr1 11 06 20 00 00 00 00 00 01 00");
  }
}
