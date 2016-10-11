#include "Common.h"

static void reboot() {
  ShellUtil::exec("sudo reboot");
}

static void updateEth(IfaceStatus& eth) {
  eth.getPlugIn() = EthtoolUtil::isPlugIn(IfconfigUtil::getEthName()) ? Bool::createTrue() : Bool::createFalse();
  if(!eth.getPlugIn().isTrue()) {
    eth.getIpv4() = "";
    eth.getDhcpStatus() = DhcpStatus::createEmpty();    
    return;
  }
  eth.getIpv4() = IfconfigUtil::getEthIp();
  if(DhcpUtil::dhcpSeverDetected()) {
    eth.getDhcpStatus() = DhcpStatus::createDhcpDetected(DhcpUtil::getDhcpServerAddress());
  } else {
    eth.getDhcpStatus() = DhcpStatus::createNoDhcpDetected();
  }
}

static void updateLte(IfaceStatus& lte) {
  lte.getPlugIn() = EthtoolUtil::isPlugIn(IfconfigUtil::getLteName()) ? Bool::createTrue() : Bool::createFalse();
  if(!lte.getPlugIn().isTrue()) {
    lte.getIpv4() = "";
    return;
  }
  lte.getIpv4() = IfconfigUtil::getLteIp();
}

template<class T>
static DynSet<T> box(T val) {
  DynSet<T> ret;
  ret.Insert(val);
  return ret;
}

static DynSet<AnsiString> empty() {
  DynSet<AnsiString> ret;
  return ret;
}

void balance(Data& data) {
  NetStatus& net = data.getNetStatus();
  IfaceStatus& eth = net.getEth();
  IfaceStatus& lte = net.getLte();
  Logger::log("[Common] Update eth\n");
  updateEth(eth);
  Logger::log("[Common] Update lte\n");
  updateLte(lte);
  
  bool EthAv = eth.getPlugIn().isTrue() && eth.getDhcpStatus().isDhcpDetected() && !eth.getGatewayPirority().isDisallow();
  Logger::log("[Common] EthPlug = " + AnsiString(eth.getPlugIn().isTrue()) + " && EthDhcpDetected " + AnsiString(eth.getDhcpStatus().isDhcpDetected()) + " && !disallow " + AnsiString(eth.getGatewayPirority().isDisallow()));
  Logger::log("[Common] EthAv = " + AnsiString(EthAv));
  bool LteAv = lte.getPlugIn().isTrue() && !lte.getGatewayPirority().isDisallow();
  Logger::log("[Common] LteAv = ("+AnsiString(lte.getPlugIn().isTrue())+" && !"+AnsiString(lte.getGatewayPirority().isDisallow())+") =" + AnsiString(LteAv));
  
  bool noEth_Lte = !EthAv && LteAv;
  Logger::log("[Common] noEth_Lte = " + AnsiString(noEth_Lte));
  bool Eth_noLte = EthAv && !LteAv;
  Logger::log("[Common] Eth_noLte = " + AnsiString(Eth_noLte));
  bool Eth_Lte = EthAv && LteAv;
  Logger::log("[Common] Eth_Lte = " + AnsiString(Eth_Lte));
  bool Eth_Lte_EthH = Eth_Lte && eth.getGatewayPirority().isHeigh();
  Logger::log("[Common] Eth_Lte_EthH = " + AnsiString(Eth_Lte_EthH));
  bool Eth_Lte_noEthH_LteH = Eth_Lte && !eth.getGatewayPirority().isHeigh() && lte.getGatewayPirority().isHeigh(); 
  Logger::log("[Common] Eth_Lte_noEthH_LteH  = " + AnsiString(Eth_Lte_noEthH_LteH ));
  bool viaEth = Eth_noLte || Eth_Lte_EthH || Eth_Lte_EthH;
  Logger::log("[Common] viaEth = " + AnsiString(viaEth));
  bool viaLte = noEth_Lte || Eth_Lte_noEthH_LteH;
  Logger::log("[Common] viaLte = " + AnsiString(viaLte));

  static bool ltePrev = false;
  static bool ethPrev = false;
  
  //todo if(!change) return;
  if(viaEth && !ethPrev) {
    ethPrev = true;
    ltePrev = false;
    Logger::log("[Common] Via Eth!");
    DhcpUtil::stopServer();
    RouteUtil::setDefault(IfconfigUtil::getEthName());
    IptablesUtil::setDefault(IfconfigUtil::getEthName(), empty());
  } else if(viaLte && !ltePrev) {
    ltePrev = true;
    ethPrev = false;
    Logger::log("[Common] Via Lte!");
    RouteUtil::setDefault(IfconfigUtil::getLteName());
    IptablesUtil::setDefault(IfconfigUtil::getLteName(), box(IfconfigUtil::getEthName()));
    IfconfigUtil::setIp(IfconfigUtil::getEthName(), "10.0.0.1");
    IfconfigUtil::setNetmask(IfconfigUtil::getEthName(), "255.255.0.0");
    if(true /*todo*/)
      DhcpUtil::startServer();
  }
}

