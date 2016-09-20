#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "AnsiString.h"
#include "MainUtils.h"
#include "Logger.h"
#include "ConfigReader.h"

int main(int argc, char* argv[]) {
  if(argc<2) {
    printf("[config file]\n");
    return 0;
  }

  ConfigObj config = ConfigReader::read(argv[1]);

  AnsiString myIp = config.getValue("settings", "my_ip");
  Logger::log("myIp:" + myIp);
  //todo
  ShellUtil::exec("sudo ifconfig eth0 " + myIp);
  AnsiString localIp = config.getValue("settings", "local_ip");
  AnsiString localPort = config.getValue("settings", "local_port");
  AnsiString apiPath = config.getValue("settings", "api_path");
  Logger::log("apiPath:" + apiPath);

  ShellUtil::exec("sudo NetBalancer /etc/TheBox/LteConfig& > /dev/null 2> /dev/null");
  while(true) {
    AnsiString cmd = "/usr/bin/wget -qO- " + apiPath;
    DynSet<AnsiString> res = ShellUtil::exec(cmd);
    printf("%s > %d\n", cmd.c_str(), res.Size());
    for(int i=0;i<res.Size();i++)
      printf("[%d]%s\n", i, res[i].c_str());
    if(res.Size()>0) {
      AnsiString hostIp = res[0].Trim();
      AnsiString hostPort = res[1].Trim();   
      AnsiString cmd2 = "TheBoxTunnel " + hostIp + " " + hostPort + " " + localIp + " " + localPort;
      printf("[cmd2]:%s\n", cmd2.c_str());
      ShellUtil::exec(cmd2);
    } else {
      Logger::log("Api Error");
    } 
    sleep(15);
  }
}
