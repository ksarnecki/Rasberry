#include "NetworkNameUtil.h"

static int Pos(const DynSet<AnsiString>& set, const AnsiString str) {
  for(int i=0;i<set.Size();i++)
    if(set[i]==str)
      return i;
  return -1;  
}

static void setSmbConfig(const AnsiString& name) {
  Logger::log("[setSmbConfig] restart");
  const AnsiString path = "/etc/samba/smb.conf";
  DynSet<AnsiString> config;
  config.Insert("[global]");
  config.Insert("workgroup = WORKGROUP");
  config.Insert("netbios name = gabinetPC");
  config.Insert("server string = gabinetPC");
  config.Insert("dns proxy = no");
  config.Insert("log file = /var/log/samba/log.%m");
  config.Insert("max log size = 1000");
  config.Insert("syslog = 0");
  config.Insert("panic action = /usr/share/samba/panic-action %d");
  config.Insert("server role = standalone server");
  config.Insert("passdb backend = tdbsam");
  config.Insert("");
  config.Insert("obey pam restrictions = yes");
  config.Insert("unix password sync = yes");
  config.Insert("passwd program = /usr/bin/passwd %u");
  config.Insert("passwd chat = *Enter\snew\s*\spassword:* %n\n *Retype\snew\s*\spassword:* %n\n *password\supdated\ssuccessfully* .");
  config.Insert("pam password change = yes");
  config.Insert("map to guest = bad user");
  config.Insert("# with the net usershare command.");
  config.Insert("usershare allow guests = yes");
  config.Insert("[homes]");
  config.Insert("comment = Home Directories");
  config.Insert("browseable = no");
  config.Insert("read only = yes");
  config.Insert("create mask = 0700");
  config.Insert("directory mask = 0700");
  config.Insert("valid users = %S");
  config.Insert("[printers]");
  config.Insert("comment = All Printers");
  config.Insert("browseable = no");
  config.Insert("path = /var/spool/samba");
  config.Insert("printable = yes");
  config.Insert("guest ok = no");
  config.Insert("read only = yes");
  config.Insert("create mask = 0700");
  config.Insert("[print$]");
  config.Insert("comment = Printer Drivers");
  config.Insert("path = /var/lib/samba/printers");
  config.Insert("browseable = yes");
  config.Insert("read only = yes");
  config.Insert("guest ok = no*/");
  ShellUtil::exec("sudo echo '' > " + path);
  for(int i=0;i<config.Size();i++) {
    ShellUtil::exec("sudo echo '" + config[i] + "' >> " + path);
  }
}

static void setNsswitchConfig() {
  const AnsiString path = "/etc/nsswitch.conf";
  DynSet<AnsiString> ret = ShellUtil::exec("sudo cat " + path);
  DynSet<AnsiString> config;
  config.Insert("passwd:         compat");
  config.Insert("group:         compat");
  config.Insert("shadow:         compat");
  config.Insert("gshadow:        files");
  config.Insert("hosts:          files dns wins");
  config.Insert("networks:       files");
  config.Insert("protocols:      db files");
  config.Insert("services:      db files");
  config.Insert("ethers:      db files");
  config.Insert("rpc:      db files");
  config.Insert("netgroup:      db files");
  bool update = false;
  for(int i=0;i<config.Size();i++) {
    if(Pos(ret, config[i])==-1)
      update = true;
  }
  if(update) {
    Logger::log("[setNsswitchConfig] update /etc/nsswitch.conf & reboot");
    ShellUtil::exec("sudo echo '' > " + path);
    for(int i=0;i<config.Size();i++) {
      ShellUtil::exec("sudo echo '" + config[i] + "' >> " + path);
    }
    ShellUtil::reboot();
  }
}

void NetworkNameUtil::setName(const AnsiString& name) {
  setNsswitchConfig();
  setSmbConfig(name);
  ShellUtil::exec("sudo service smb restart");
}
