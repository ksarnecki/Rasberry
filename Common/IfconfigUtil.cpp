#include "IfconfigUtil.h"

AnsiString IfconfigUtil::getEthName() { 
 return "eth0";
}

AnsiString IfconfigUtil::getLteName() {
  return "eth1";
}

AnsiString IfconfigUtil::getWifiName() {
  return "wlan0";
}

AnsiString IfconfigUtil::getEthIp() {
  DynSet<AnsiString> res = ShellUtil::exec("sudo /sbin/ifconfig " + getEthName() + " | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}'");
  if(res.Size()>0)
    return res[0];
  return "";
}

AnsiString IfconfigUtil::getLteIp() {
  DynSet<AnsiString> res = ShellUtil::exec("sudo /sbin/ifconfig " + getLteName() + " | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}'");
  if(res.Size()>0)
    return res[0];
  return "";
}

void IfconfigUtil::setIp(const AnsiString& iface, const AnsiString& ip) {
  Logger::log("[IfconfigUtil][setIp] " + iface + " " + ip);
  ShellUtil::exec("sudo /sbin/ifconfig " + iface + " " + ip);
}

void IfconfigUtil::setNetmask(const AnsiString& iface, const AnsiString& mask) {
  Logger::log("[IfconfigUtil][setNetmask] " + iface + " " + mask);
  ShellUtil::exec("sudo /sbin/ifconfig " + iface + " netmask" + mask);
}
