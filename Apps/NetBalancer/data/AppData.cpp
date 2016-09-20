
#include "AppData.h"
#include "Exception.h"
//------------- string ---------------
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- Bool ---------------
const int Bool::_TypeTrue = 0;
const int Bool::_TypeFalse = 1;
void Bool::init(int type, void* ptr) {
  if (type==_TypeTrue) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeFalse) {
    _type = type;
    _ptr = 0;
  }
}
void Bool::clean() {
  if (_type==_TypeTrue) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Bool::clean()");
  } else if (_type==_TypeFalse) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Bool::clean()");
  }
}
Bool::Bool() : _type(-1), _ptr(0) {
}
Bool::Bool(const Bool& _value) {
  init(_value._type, _value._ptr);
}
Bool& Bool::operator=(const Bool& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Bool::isTrue() const {
  return _type==_TypeTrue;
}
bool Bool::isFalse() const {
  return _type==_TypeFalse;
}


Bool::~Bool() {
  clean();
}
Bool Bool::createTrue() {
  Bool _value;
  _value._type = _TypeTrue;
  _value._ptr = 0;
  return _value;
}
Bool Bool::createFalse() {
  Bool _value;
  _value._type = _TypeFalse;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- DhcpStatus ---------------
const int DhcpStatus::_TypeEmpty = 0;
const int DhcpStatus::_TypeDhcpDetected = 1;
const int DhcpStatus::_TypeNoDhcpDetected = 2;
const int DhcpStatus::_TypeDhcpRun = 3;
void DhcpStatus::init(int type, void* ptr) {
  if (type==_TypeEmpty) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDhcpDetected) {
    _type = type;
    _ptr = new AnsiString(*(AnsiString*) ptr);
  } else if (type==_TypeNoDhcpDetected) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeDhcpRun) {
    _type = type;
    _ptr = 0;
  }
}
void DhcpStatus::clean() {
  if (_type==_TypeEmpty) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DhcpStatus::clean()");
  } else if (_type==_TypeDhcpDetected) {
    _type = -1;
    delete (AnsiString*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeNoDhcpDetected) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DhcpStatus::clean()");
  } else if (_type==_TypeDhcpRun) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("DhcpStatus::clean()");
  }
}
DhcpStatus::DhcpStatus() : _type(-1), _ptr(0) {
}
DhcpStatus::DhcpStatus(const DhcpStatus& _value) {
  init(_value._type, _value._ptr);
}
DhcpStatus& DhcpStatus::operator=(const DhcpStatus& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool DhcpStatus::isEmpty() const {
  return _type==_TypeEmpty;
}
bool DhcpStatus::isDhcpDetected() const {
  return _type==_TypeDhcpDetected;
}
bool DhcpStatus::isNoDhcpDetected() const {
  return _type==_TypeNoDhcpDetected;
}
bool DhcpStatus::isDhcpRun() const {
  return _type==_TypeDhcpRun;
}
const AnsiString& DhcpStatus::asDhcpDetected() const {
  if (_type!=_TypeDhcpDetected)
    throw Exception("DhcpStatus::asDhcpDetected");
  return *(AnsiString*) _ptr;
}
AnsiString& DhcpStatus::asDhcpDetected() {
  if (_type!=_TypeDhcpDetected)
    throw Exception("DhcpStatus::asDhcpDetected");
  return *(AnsiString*) _ptr;
}


DhcpStatus::~DhcpStatus() {
  clean();
}
DhcpStatus DhcpStatus::createEmpty() {
  DhcpStatus _value;
  _value._type = _TypeEmpty;
  _value._ptr = 0;
  return _value;
}
DhcpStatus DhcpStatus::createDhcpDetected(const AnsiString& _param) {
  DhcpStatus _value;
  _value._type = _TypeDhcpDetected;
  _value._ptr = new AnsiString(_param);
  return _value;
}
DhcpStatus DhcpStatus::createNoDhcpDetected() {
  DhcpStatus _value;
  _value._type = _TypeNoDhcpDetected;
  _value._ptr = 0;
  return _value;
}
DhcpStatus DhcpStatus::createDhcpRun() {
  DhcpStatus _value;
  _value._type = _TypeDhcpRun;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- GatewayPirority ---------------
const int GatewayPirority::_TypeDisallow = 0;
const int GatewayPirority::_TypeLow = 1;
const int GatewayPirority::_TypeHeigh = 2;
void GatewayPirority::init(int type, void* ptr) {
  if (type==_TypeDisallow) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeLow) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeHeigh) {
    _type = type;
    _ptr = 0;
  }
}
void GatewayPirority::clean() {
  if (_type==_TypeDisallow) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("GatewayPirority::clean()");
  } else if (_type==_TypeLow) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("GatewayPirority::clean()");
  } else if (_type==_TypeHeigh) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("GatewayPirority::clean()");
  }
}
GatewayPirority::GatewayPirority() : _type(-1), _ptr(0) {
}
GatewayPirority::GatewayPirority(const GatewayPirority& _value) {
  init(_value._type, _value._ptr);
}
GatewayPirority& GatewayPirority::operator=(const GatewayPirority& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool GatewayPirority::isDisallow() const {
  return _type==_TypeDisallow;
}
bool GatewayPirority::isLow() const {
  return _type==_TypeLow;
}
bool GatewayPirority::isHeigh() const {
  return _type==_TypeHeigh;
}


GatewayPirority::~GatewayPirority() {
  clean();
}
GatewayPirority GatewayPirority::createDisallow() {
  GatewayPirority _value;
  _value._type = _TypeDisallow;
  _value._ptr = 0;
  return _value;
}
GatewayPirority GatewayPirority::createLow() {
  GatewayPirority _value;
  _value._type = _TypeLow;
  _value._ptr = 0;
  return _value;
}
GatewayPirority GatewayPirority::createHeigh() {
  GatewayPirority _value;
  _value._type = _TypeHeigh;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- IfaceStatus ---------------
IfaceStatus::IfaceStatus(const Bool& _plugIn, const AnsiString& _ipv4, const DhcpStatus& _dhcpStatus, const Bool& _pingOk, const GatewayPirority& _gatewayPirority) : plugIn(_plugIn), ipv4(_ipv4), dhcpStatus(_dhcpStatus), pingOk(_pingOk), gatewayPirority(_gatewayPirority) {
}
const Bool& IfaceStatus::getPlugIn() const {
  return plugIn;
}
Bool& IfaceStatus::getPlugIn() {
  return plugIn;
}
const AnsiString& IfaceStatus::getIpv4() const {
  return ipv4;
}
AnsiString& IfaceStatus::getIpv4() {
  return ipv4;
}
const DhcpStatus& IfaceStatus::getDhcpStatus() const {
  return dhcpStatus;
}
DhcpStatus& IfaceStatus::getDhcpStatus() {
  return dhcpStatus;
}
const Bool& IfaceStatus::getPingOk() const {
  return pingOk;
}
Bool& IfaceStatus::getPingOk() {
  return pingOk;
}
const GatewayPirority& IfaceStatus::getGatewayPirority() const {
  return gatewayPirority;
}
GatewayPirority& IfaceStatus::getGatewayPirority() {
  return gatewayPirority;
}
IfaceStatus::~IfaceStatus() {
}
//----------------------------------

//------------- WifiNetwork ---------------
WifiNetwork::WifiNetwork(const AnsiString& _ssid, const Bool& _connected) : ssid(_ssid), connected(_connected) {
}
const AnsiString& WifiNetwork::getSsid() const {
  return ssid;
}
AnsiString& WifiNetwork::getSsid() {
  return ssid;
}
const Bool& WifiNetwork::getConnected() const {
  return connected;
}
Bool& WifiNetwork::getConnected() {
  return connected;
}
WifiNetwork::~WifiNetwork() {
}
//----------------------------------

//------------- WifiList ---------------
WifiList::WifiList() {
}
WifiList::~WifiList() {
}
//----------------------------------

//------------- NetStatus ---------------
NetStatus::NetStatus(const IfaceStatus& _eth, const IfaceStatus& _wlan, const IfaceStatus& _lte, const WifiList& _wifiList) : eth(_eth), wlan(_wlan), lte(_lte), wifiList(_wifiList) {
}
const IfaceStatus& NetStatus::getEth() const {
  return eth;
}
IfaceStatus& NetStatus::getEth() {
  return eth;
}
const IfaceStatus& NetStatus::getWlan() const {
  return wlan;
}
IfaceStatus& NetStatus::getWlan() {
  return wlan;
}
const IfaceStatus& NetStatus::getLte() const {
  return lte;
}
IfaceStatus& NetStatus::getLte() {
  return lte;
}
const WifiList& NetStatus::getWifiList() const {
  return wifiList;
}
WifiList& NetStatus::getWifiList() {
  return wifiList;
}
NetStatus::~NetStatus() {
}
//----------------------------------

//------------- System ---------------
const int System::_TypeUbuntu = 0;
const int System::_TypeRasbian = 1;
void System::init(int type, void* ptr) {
  if (type==_TypeUbuntu) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeRasbian) {
    _type = type;
    _ptr = 0;
  }
}
void System::clean() {
  if (_type==_TypeUbuntu) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("System::clean()");
  } else if (_type==_TypeRasbian) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("System::clean()");
  }
}
System::System() : _type(-1), _ptr(0) {
}
System::System(const System& _value) {
  init(_value._type, _value._ptr);
}
System& System::operator=(const System& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool System::isUbuntu() const {
  return _type==_TypeUbuntu;
}
bool System::isRasbian() const {
  return _type==_TypeRasbian;
}


System::~System() {
  clean();
}
System System::createUbuntu() {
  System _value;
  _value._type = _TypeUbuntu;
  _value._ptr = 0;
  return _value;
}
System System::createRasbian() {
  System _value;
  _value._type = _TypeRasbian;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- Device ---------------
const int Device::_TypeRPI = 0;
const int Device::_TypeBPI = 1;
void Device::init(int type, void* ptr) {
  if (type==_TypeRPI) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeBPI) {
    _type = type;
    _ptr = 0;
  }
}
void Device::clean() {
  if (_type==_TypeRPI) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Device::clean()");
  } else if (_type==_TypeBPI) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Device::clean()");
  }
}
Device::Device() : _type(-1), _ptr(0) {
}
Device::Device(const Device& _value) {
  init(_value._type, _value._ptr);
}
Device& Device::operator=(const Device& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Device::isRPI() const {
  return _type==_TypeRPI;
}
bool Device::isBPI() const {
  return _type==_TypeBPI;
}


Device::~Device() {
  clean();
}
Device Device::createRPI() {
  Device _value;
  _value._type = _TypeRPI;
  _value._ptr = 0;
  return _value;
}
Device Device::createBPI() {
  Device _value;
  _value._type = _TypeBPI;
  _value._ptr = 0;
  return _value;
}


//----------------------------------

//------------- Data ---------------
Data::Data(const NetStatus& _netStatus, const System& _system, const Device& _device) : netStatus(_netStatus), system(_system), device(_device) {
}
const NetStatus& Data::getNetStatus() const {
  return netStatus;
}
NetStatus& Data::getNetStatus() {
  return netStatus;
}
const System& Data::getSystem() const {
  return system;
}
System& Data::getSystem() {
  return system;
}
const Device& Data::getDevice() const {
  return device;
}
Device& Data::getDevice() {
  return device;
}
Data::~Data() {
}
//----------------------------------

