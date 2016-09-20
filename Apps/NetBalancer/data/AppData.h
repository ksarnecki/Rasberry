#ifndef _APPDATA_GEN_H_
#define _APPDATA_GEN_H_
#include "DynSet.h"
//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- Bool ---------------
class Bool {
  int _type;
  void* _ptr;

  static const int _TypeTrue;
  static const int _TypeFalse;

  virtual void init(int, void*);
  virtual void clean();
  Bool();
public:
  Bool(const Bool&);
  virtual Bool& operator=(const Bool&);

  virtual bool isTrue() const;
  virtual bool isFalse() const;



  virtual ~Bool();

  static Bool createTrue();
  static Bool createFalse();

};
//----------------------------------

//------------- DhcpStatus ---------------
class DhcpStatus {
  int _type;
  void* _ptr;

  static const int _TypeEmpty;
  static const int _TypeDhcpDetected;
  static const int _TypeNoDhcpDetected;
  static const int _TypeDhcpRun;

  virtual void init(int, void*);
  virtual void clean();
  DhcpStatus();
public:
  DhcpStatus(const DhcpStatus&);
  virtual DhcpStatus& operator=(const DhcpStatus&);

  virtual bool isEmpty() const;
  virtual bool isDhcpDetected() const;
  virtual bool isNoDhcpDetected() const;
  virtual bool isDhcpRun() const;

  virtual const AnsiString& asDhcpDetected() const;
  virtual AnsiString& asDhcpDetected();


  virtual ~DhcpStatus();

  static DhcpStatus createEmpty();
  static DhcpStatus createDhcpDetected(const AnsiString&);
  static DhcpStatus createNoDhcpDetected();
  static DhcpStatus createDhcpRun();

};
//----------------------------------

//------------- GatewayPirority ---------------
class GatewayPirority {
  int _type;
  void* _ptr;

  static const int _TypeDisallow;
  static const int _TypeLow;
  static const int _TypeHeigh;

  virtual void init(int, void*);
  virtual void clean();
  GatewayPirority();
public:
  GatewayPirority(const GatewayPirority&);
  virtual GatewayPirority& operator=(const GatewayPirority&);

  virtual bool isDisallow() const;
  virtual bool isLow() const;
  virtual bool isHeigh() const;



  virtual ~GatewayPirority();

  static GatewayPirority createDisallow();
  static GatewayPirority createLow();
  static GatewayPirority createHeigh();

};
//----------------------------------

//------------- IfaceStatus ---------------
class IfaceStatus {
  Bool plugIn;
  AnsiString ipv4;
  DhcpStatus dhcpStatus;
  Bool pingOk;
  GatewayPirority gatewayPirority;
public:
  IfaceStatus(const Bool&, const AnsiString&, const DhcpStatus&, const Bool&, const GatewayPirority&);
  virtual const Bool& getPlugIn() const;
  virtual const AnsiString& getIpv4() const;
  virtual const DhcpStatus& getDhcpStatus() const;
  virtual const Bool& getPingOk() const;
  virtual const GatewayPirority& getGatewayPirority() const;
  virtual Bool& getPlugIn();
  virtual AnsiString& getIpv4();
  virtual DhcpStatus& getDhcpStatus();
  virtual Bool& getPingOk();
  virtual GatewayPirority& getGatewayPirority();


  virtual ~IfaceStatus();

};
//----------------------------------

//------------- WifiNetwork ---------------
class WifiNetwork {
  AnsiString ssid;
  Bool connected;
public:
  WifiNetwork(const AnsiString&, const Bool&);
  virtual const AnsiString& getSsid() const;
  virtual const Bool& getConnected() const;
  virtual AnsiString& getSsid();
  virtual Bool& getConnected();


  virtual ~WifiNetwork();

};
//----------------------------------

//------------- WifiList ---------------
#include "DynSet.h"


class WifiList : public DynSet<WifiNetwork> {
public:
  WifiList();


  virtual ~WifiList();

};
//----------------------------------

//------------- NetStatus ---------------
class NetStatus {
  IfaceStatus eth;
  IfaceStatus wlan;
  IfaceStatus lte;
  WifiList wifiList;
public:
  NetStatus(const IfaceStatus&, const IfaceStatus&, const IfaceStatus&, const WifiList&);
  virtual const IfaceStatus& getEth() const;
  virtual const IfaceStatus& getWlan() const;
  virtual const IfaceStatus& getLte() const;
  virtual const WifiList& getWifiList() const;
  virtual IfaceStatus& getEth();
  virtual IfaceStatus& getWlan();
  virtual IfaceStatus& getLte();
  virtual WifiList& getWifiList();


  virtual ~NetStatus();

};
//----------------------------------

//------------- System ---------------
class System {
  int _type;
  void* _ptr;

  static const int _TypeUbuntu;
  static const int _TypeRasbian;

  virtual void init(int, void*);
  virtual void clean();
  System();
public:
  System(const System&);
  virtual System& operator=(const System&);

  virtual bool isUbuntu() const;
  virtual bool isRasbian() const;



  virtual ~System();

  static System createUbuntu();
  static System createRasbian();

};
//----------------------------------

//------------- Device ---------------
class Device {
  int _type;
  void* _ptr;

  static const int _TypeRPI;
  static const int _TypeBPI;

  virtual void init(int, void*);
  virtual void clean();
  Device();
public:
  Device(const Device&);
  virtual Device& operator=(const Device&);

  virtual bool isRPI() const;
  virtual bool isBPI() const;



  virtual ~Device();

  static Device createRPI();
  static Device createBPI();

};
//----------------------------------

//------------- Data ---------------
class Data {
  NetStatus netStatus;
  System system;
  Device device;
public:
  Data(const NetStatus&, const System&, const Device&);
  virtual const NetStatus& getNetStatus() const;
  virtual const System& getSystem() const;
  virtual const Device& getDevice() const;
  virtual NetStatus& getNetStatus();
  virtual System& getSystem();
  virtual Device& getDevice();


  virtual ~Data();

};
//----------------------------------

#endif
