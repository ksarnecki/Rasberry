#include "DhcpUtil.h"

void DhcpUtil::setConfig() {
  Logger::log("[DhcpUtil] setConfig");
  const AnsiString path = "/etc/dhcp/dhcpd.conf";
  DynSet<AnsiString> config;
  config.Insert("ddns-update-style none;");
  config.Insert("authoritative;");
  config.Insert("log-facility local7;");
  config.Insert("subnet 10.0.0.0 netmask 255.255.0.0 {");
  config.Insert("range 10.0.0.128 10.0.0.254;");
  config.Insert("option broadcast-address 10.0.255.255;");
  config.Insert("option routers 10.0.0.1;");
  config.Insert("default-lease-time 18000;");
  config.Insert("max-lease-time 36000;");
  config.Insert("}");
  ShellUtil::exec("sudo echo '' > " + path);
  for(int i=0;i<config.Size();i++) {
    ShellUtil::exec("sudo echo '" + config[i] + "' >> " + path);
  }
}

void DhcpUtil::startServer() {
  Logger::log("[DhcpUtil] startServer");
  if(!ShellUtil::ServiceExist("isc-dhcp-server"))
    throw Exception("isc-dhcp-server not found!");
  setConfig();
  ShellUtil::exec("sudo service isc-dhcp-server start");
  ShellUtil::exec("sudo service isc-dhcp-server restart");
}

void DhcpUtil::stopServer() {
  Logger::log("[DhcpUtil] stopServer");
  if(!ShellUtil::ServiceExist("isc-dhcp-server"))
    throw Exception("isc-dhcp-server not found!");
  ShellUtil::exec("sudo service isc-dhcp-server stop");
}

bool DhcpUtil::dhcpSeverDetected() {
  if(!ShellUtil::CmdExist("dhcpcd"))
    throw Exception("dhcpcd not found!");
  // return ShellUtil::exec("sudo dhcpcd -T " + IfconfigUtil::getEthName() + " -t 3 | grep new_ip").Size() > 0; on Rasberry PI & Rasbian
  return ShellUtil::exec("sudo dhcpcd -T " + IfconfigUtil::getEthName() + " -t 3 | grep IPADDR").Size() > 0;
}

AnsiString DhcpUtil::getDhcpServerAddress() {
  if(!ShellUtil::CmdExist("dhcpcd"))
    throw Exception("dhcpcd not found!");
  DynSet<AnsiString> res = ShellUtil::exec("sudo dhcpcd -T " + IfconfigUtil::getEthName() + " -t 3 | grep new_ip");
  if(res.Size()<=0)
    return "";
  int ix = res[0].Pos("'")+1;
  return res[0].SubString(ix, res[0].Length()-ix).c_str();
}
