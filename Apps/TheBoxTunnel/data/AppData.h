#ifndef _APPDATA_GEN_H_
#define _APPDATA_GEN_H_
#include "DynSet.h"
#include "SimpleData.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- Data ---------------
class Data {
  int id;
  AnsiString source;
public:
  Data(const int&, const AnsiString&);
  virtual const int& getId() const;
  virtual const AnsiString& getSource() const;
  virtual int& getId();
  virtual AnsiString& getSource();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~Data();

  static Data fromSimpleData(const SimpleData&);
  static Data fromBinary(BinaryReader&);
};
//----------------------------------

//------------- NewClientInfo ---------------
class NewClientInfo {
  int id;
  int connport;
public:
  NewClientInfo(const int&, const int&);
  virtual const int& getId() const;
  virtual const int& getConnport() const;
  virtual int& getId();
  virtual int& getConnport();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~NewClientInfo();

  static NewClientInfo fromSimpleData(const SimpleData&);
  static NewClientInfo fromBinary(BinaryReader&);
};
//----------------------------------

//------------- Cmd ---------------
class Cmd {
  int _type;
  void* _ptr;

  static const int _TypePing;
  static const int _TypeNewClient;
  static const int _TypeClientLost;
  static const int _TypeClientAccept;
  static const int _TypeData;

  virtual void init(int, void*);
  virtual void clean();
  Cmd();
public:
  Cmd(const Cmd&);
  virtual Cmd& operator=(const Cmd&);

  virtual bool isPing() const;
  virtual bool isNewClient() const;
  virtual bool isClientLost() const;
  virtual bool isClientAccept() const;
  virtual bool isData() const;

  virtual const NewClientInfo& asNewClient() const;
  virtual NewClientInfo& asNewClient();
  virtual const int& asClientLost() const;
  virtual int& asClientLost();
  virtual const int& asClientAccept() const;
  virtual int& asClientAccept();
  virtual const Data& asData() const;
  virtual Data& asData();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~Cmd();

  static Cmd createPing();
  static Cmd createNewClient(const NewClientInfo&);
  static Cmd createClientLost(const int&);
  static Cmd createClientAccept(const int&);
  static Cmd createData(const Data&);

  static Cmd fromSimpleData(const SimpleData&);
  static Cmd fromBinary(BinaryReader&);
};
//----------------------------------

//------------- FdsArray ---------------
#include "DynSet.h"


class FdsArray : public DynSet<int> {
public:
  FdsArray();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~FdsArray();

  static FdsArray fromSimpleData(const SimpleData&);
  static FdsArray fromBinary(BinaryReader&);
};
//----------------------------------

//------------- Client ---------------
class Client {
  AnsiString outbuf;
  int id;
  int fd;
public:
  Client(const AnsiString&, const int&, const int&);
  virtual const AnsiString& getOutbuf() const;
  virtual const int& getId() const;
  virtual const int& getFd() const;
  virtual AnsiString& getOutbuf();
  virtual int& getId();
  virtual int& getFd();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~Client();

  static Client fromSimpleData(const SimpleData&);
  static Client fromBinary(BinaryReader&);
};
//----------------------------------

//------------- ConnClientsArray ---------------
#include "DynSet.h"


class ConnClientsArray : public DynSet<Client> {
public:
  ConnClientsArray();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~ConnClientsArray();

  static ConnClientsArray fromSimpleData(const SimpleData&);
  static ConnClientsArray fromBinary(BinaryReader&);
};
//----------------------------------

//------------- ConnData ---------------
class ConnData {
  ConnClientsArray tcpclients;
  FdsArray listenfds;
  int fd;
  int sfd;
  AnsiString inbuf;
  AnsiString outbuf;
  int lastread;
  int lastwrite;
public:
  ConnData(const ConnClientsArray&, const FdsArray&, const int&, const int&, const AnsiString&, const AnsiString&, const int&, const int&);
  virtual const ConnClientsArray& getTcpclients() const;
  virtual const FdsArray& getListenfds() const;
  virtual const int& getFd() const;
  virtual const int& getSfd() const;
  virtual const AnsiString& getInbuf() const;
  virtual const AnsiString& getOutbuf() const;
  virtual const int& getLastread() const;
  virtual const int& getLastwrite() const;
  virtual ConnClientsArray& getTcpclients();
  virtual FdsArray& getListenfds();
  virtual int& getFd();
  virtual int& getSfd();
  virtual AnsiString& getInbuf();
  virtual AnsiString& getOutbuf();
  virtual int& getLastread();
  virtual int& getLastwrite();

  virtual SimpleData toSimpleData() const;
  virtual void toBinary(BinaryWriter&) const;
  virtual AnsiString toXML() const;

  virtual ~ConnData();

  static ConnData fromSimpleData(const SimpleData&);
  static ConnData fromBinary(BinaryReader&);
};
//----------------------------------

#endif
