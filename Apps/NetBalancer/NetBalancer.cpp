#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "AnsiString.h"
#include "data/AppData.h"
#include "ShellUtil.h"
#include "LteUtil.h"
#include "Logger.h"
#include "Common.h"
#include "ConfigReader.h"
#include "NetworkNameUtil.h"

#define MAX_NET_CHECK 15

void onStart(Data& data) {
  Logger::log("[onStart] start\n");
  ShellUtil::exec("for f in /proc/sys/net/ipv4/conf/*/rp_filter; do echo 0 >| $f ; done");
  NetworkNameUtil::setName("GABINET_PC");
  Logger::log("[onStart] end\n");
}

Data load(const AnsiString& path) {
  /*
  * Default settings
  */
  IfaceStatus eth(Bool::createFalse(), "", DhcpStatus::createEmpty(), Bool::createFalse(), GatewayPirority::createLow());
  IfaceStatus lte(Bool::createFalse(), "", DhcpStatus::createEmpty(), Bool::createFalse(), GatewayPirority::createHeigh());
  IfaceStatus wifi(Bool::createFalse(), "", DhcpStatus::createEmpty(), Bool::createFalse(), GatewayPirority::createDisallow());
  Data data = Data(NetStatus(eth, wifi, lte, WifiList()), System::createRasbian(), Device::createRPI());

  ConfigObj config = ConfigReader::read(path);

  const AnsiString eth_dhcp = config.getValue("eth", "dhcp");
  const AnsiString eth_gateway = config.getValue("eth", "gateway");
  const AnsiString lte_gateway = config.getValue("lte", "gateway");

  if(eth_gateway=="heigh") 
    data.getNetStatus().getEth().getGatewayPirority() = GatewayPirority::createHeigh();
  if(eth_gateway=="low") 
    data.getNetStatus().getEth().getGatewayPirority() = GatewayPirority::createLow();
  if(eth_gateway=="disallow") 
    data.getNetStatus().getEth().getGatewayPirority() = GatewayPirority::GatewayPirority::createDisallow();

  if(lte_gateway=="heigh") 
    data.getNetStatus().getLte().getGatewayPirority() = GatewayPirority::createHeigh();
  if(lte_gateway=="low") 
    data.getNetStatus().getLte().getGatewayPirority() = GatewayPirority::createLow();
  if(lte_gateway=="disallow") 
    data.getNetStatus().getLte().getGatewayPirority() = GatewayPirority::GatewayPirority::createDisallow();

  return data;
}

int main(int argc, char* argv[]) {
  /*
  * Konfiguracja!
  */
  if(argc<2) {
    printf("[Config file path]\n");
    return 0;
  }
  Data data = load(argv[1]);
  /*
  * Odpalenie serwerów.
  */
  onStart(data);
  /*
  * Uruchomienie głównego wątku.
  */
  int lastNetCheck=MAX_NET_CHECK;
  while(true) {
    try {
      if(++lastNetCheck>=MAX_NET_CHECK) {
        /*
        * Zmiana konfiguracji ustawień sieciowcyh
        */
        Logger::log("balance");
        
        balance(data);
        
        lastNetCheck=0;
      }
      /*
      * zamontowanie modemu lte
      */
      LteUtil::mount();
      Logger::log("sleep...");
      sleep(10);
    } catch(Exception e) {
      Logger::log("E: "+e.Message);
    }
  }
}
