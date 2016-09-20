
#include "AppData.h"
#include "Exception.h"
//------------- int ---------------
//----------------------------------

//------------- string ---------------
//----------------------------------

//------------- Data ---------------
Data::Data(const int& _id, const AnsiString& _source) : id(_id), source(_source) {
}
const int& Data::getId() const {
  return id;
}
int& Data::getId() {
  return id;
}
const AnsiString& Data::getSource() const {
  return source;
}
AnsiString& Data::getSource() {
  return source;
}
void Data::toBinary(BinaryWriter& writer) const {
  writer << id;
  writer << source;
}
SimpleData Data::toSimpleData() const {
  SimpleRecord _record;
  _record.add("id", SimpleData::createInt(id));
  _record.add("source", SimpleData::createString(source));
  return SimpleData::createRecord(_record);
}
AnsiString Data::toXML() const {
  AnsiString _xml = "<Data>";
    _xml += "<id><![CDATA[" + AnsiString(id)+"]]></id>";
    _xml += "<source><![CDATA[" + AnsiString(source)+"]]></source>";
  _xml += "</Data>";
  return _xml;
}
Data::~Data() {
}
Data Data::fromBinary(BinaryReader& reader) {
  int _id;
  reader >> _id;
  AnsiString _source;
  reader >> _source;
  return Data(_id, _source);
}
Data Data::fromSimpleData(const SimpleData& _data) {
  const SimpleRecord& _record = _data.asRecord();
  return Data(_record["id"].asInt(), _record["source"].asString());
}
//----------------------------------

//------------- NewClientInfo ---------------
NewClientInfo::NewClientInfo(const int& _id, const int& _connport) : id(_id), connport(_connport) {
}
const int& NewClientInfo::getId() const {
  return id;
}
int& NewClientInfo::getId() {
  return id;
}
const int& NewClientInfo::getConnport() const {
  return connport;
}
int& NewClientInfo::getConnport() {
  return connport;
}
void NewClientInfo::toBinary(BinaryWriter& writer) const {
  writer << id;
  writer << connport;
}
SimpleData NewClientInfo::toSimpleData() const {
  SimpleRecord _record;
  _record.add("id", SimpleData::createInt(id));
  _record.add("connport", SimpleData::createInt(connport));
  return SimpleData::createRecord(_record);
}
AnsiString NewClientInfo::toXML() const {
  AnsiString _xml = "<NewClientInfo>";
    _xml += "<id><![CDATA[" + AnsiString(id)+"]]></id>";
    _xml += "<connport><![CDATA[" + AnsiString(connport)+"]]></connport>";
  _xml += "</NewClientInfo>";
  return _xml;
}
NewClientInfo::~NewClientInfo() {
}
NewClientInfo NewClientInfo::fromBinary(BinaryReader& reader) {
  int _id;
  reader >> _id;
  int _connport;
  reader >> _connport;
  return NewClientInfo(_id, _connport);
}
NewClientInfo NewClientInfo::fromSimpleData(const SimpleData& _data) {
  const SimpleRecord& _record = _data.asRecord();
  return NewClientInfo(_record["id"].asInt(), _record["connport"].asInt());
}
//----------------------------------

//------------- Cmd ---------------
const int Cmd::_TypePing = 0;
const int Cmd::_TypeNewClient = 1;
const int Cmd::_TypeClientLost = 2;
const int Cmd::_TypeClientAccept = 3;
const int Cmd::_TypeData = 4;
void Cmd::init(int type, void* ptr) {
  if (type==_TypePing) {
    _type = type;
    _ptr = 0;
  } else if (type==_TypeNewClient) {
    _type = type;
    _ptr = new NewClientInfo(*(NewClientInfo*) ptr);
  } else if (type==_TypeClientLost) {
    _type = type;
    _ptr = new int(*(int*) ptr);
  } else if (type==_TypeClientAccept) {
    _type = type;
    _ptr = new int(*(int*) ptr);
  } else if (type==_TypeData) {
    _type = type;
    _ptr = new Data(*(Data*) ptr);
  }
}
void Cmd::clean() {
  if (_type==_TypePing) {
    _type = -1;
    if (_ptr!=0)
      throw Exception("Cmd::clean()");
  } else if (_type==_TypeNewClient) {
    _type = -1;
    delete (NewClientInfo*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeClientLost) {
    _type = -1;
    delete (int*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeClientAccept) {
    _type = -1;
    delete (int*) _ptr;
    _ptr = 0;
  } else if (_type==_TypeData) {
    _type = -1;
    delete (Data*) _ptr;
    _ptr = 0;
  }
}
Cmd::Cmd() : _type(-1), _ptr(0) {
}
Cmd::Cmd(const Cmd& _value) {
  init(_value._type, _value._ptr);
}
Cmd& Cmd::operator=(const Cmd& _value) {
  clean();
  init(_value._type, _value._ptr);
  return *this;
}
bool Cmd::isPing() const {
  return _type==_TypePing;
}
bool Cmd::isNewClient() const {
  return _type==_TypeNewClient;
}
bool Cmd::isClientLost() const {
  return _type==_TypeClientLost;
}
bool Cmd::isClientAccept() const {
  return _type==_TypeClientAccept;
}
bool Cmd::isData() const {
  return _type==_TypeData;
}
const NewClientInfo& Cmd::asNewClient() const {
  if (_type!=_TypeNewClient)
    throw Exception("Cmd::asNewClient");
  return *(NewClientInfo*) _ptr;
}
NewClientInfo& Cmd::asNewClient() {
  if (_type!=_TypeNewClient)
    throw Exception("Cmd::asNewClient");
  return *(NewClientInfo*) _ptr;
}
const int& Cmd::asClientLost() const {
  if (_type!=_TypeClientLost)
    throw Exception("Cmd::asClientLost");
  return *(int*) _ptr;
}
int& Cmd::asClientLost() {
  if (_type!=_TypeClientLost)
    throw Exception("Cmd::asClientLost");
  return *(int*) _ptr;
}
const int& Cmd::asClientAccept() const {
  if (_type!=_TypeClientAccept)
    throw Exception("Cmd::asClientAccept");
  return *(int*) _ptr;
}
int& Cmd::asClientAccept() {
  if (_type!=_TypeClientAccept)
    throw Exception("Cmd::asClientAccept");
  return *(int*) _ptr;
}
const Data& Cmd::asData() const {
  if (_type!=_TypeData)
    throw Exception("Cmd::asData");
  return *(Data*) _ptr;
}
Data& Cmd::asData() {
  if (_type!=_TypeData)
    throw Exception("Cmd::asData");
  return *(Data*) _ptr;
}

void Cmd::toBinary(BinaryWriter& writer) const {
  writer << _type;
  if (_type==_TypePing)
    ;
  else if (_type==_TypeNewClient)
    ((NewClientInfo*) _ptr)->toBinary(writer);
  else if (_type==_TypeClientLost)
    writer << (*(int*) _ptr);
  else if (_type==_TypeClientAccept)
    writer << (*(int*) _ptr);
  else if (_type==_TypeData)
    ((Data*) _ptr)->toBinary(writer);
  else
    throw Exception("Cmd::toBinary");
}
SimpleData Cmd::toSimpleData() const {
if (_type==_TypePing)
    return SimpleData::createVariant(SimpleVariant("ping", SimpleData::createInt(-1)));
  else if (_type==_TypeNewClient)
    return SimpleData::createVariant(SimpleVariant("newClient", ((NewClientInfo*) _ptr)->toSimpleData()));
  else if (_type==_TypeClientLost)
    return SimpleData::createVariant(SimpleVariant("clientLost", SimpleData::createInt(*(int*) _ptr)));
  else if (_type==_TypeClientAccept)
    return SimpleData::createVariant(SimpleVariant("clientAccept", SimpleData::createInt(*(int*) _ptr)));
  else if (_type==_TypeData)
    return SimpleData::createVariant(SimpleVariant("data", ((Data*) _ptr)->toSimpleData()));
  else
    throw Exception("Cmd::toSimpleData");
}
AnsiString Cmd::toXML() const {
  AnsiString _xml = "<Cmd>";
    if (_type==0)
      _xml += "<ping/>";
    else if (_type==1)
    _xml += "<newClient>" + ((NewClientInfo*) _ptr)->toXML() + "</newClient>";
    else if (_type==2)
    _xml += "<clientLost><![CDATA[" + AnsiString(*((int*) _ptr)) + "]]></clientLost>";
    else if (_type==3)
    _xml += "<clientAccept><![CDATA[" + AnsiString(*((int*) _ptr)) + "]]></clientAccept>";
    else if (_type==4)
    _xml += "<data>" + ((Data*) _ptr)->toXML() + "</data>";
    else
      throw Exception("Cmd::toXML(" + AnsiString(_type) + ")");
    _xml += "</Cmd>";
    return _xml;
}

Cmd::~Cmd() {
  clean();
}
Cmd Cmd::createPing() {
  Cmd _value;
  _value._type = _TypePing;
  _value._ptr = 0;
  return _value;
}
Cmd Cmd::createNewClient(const NewClientInfo& _param) {
  Cmd _value;
  _value._type = _TypeNewClient;
  _value._ptr = new NewClientInfo(_param);
  return _value;
}
Cmd Cmd::createClientLost(const int& _param) {
  Cmd _value;
  _value._type = _TypeClientLost;
  _value._ptr = new int(_param);
  return _value;
}
Cmd Cmd::createClientAccept(const int& _param) {
  Cmd _value;
  _value._type = _TypeClientAccept;
  _value._ptr = new int(_param);
  return _value;
}
Cmd Cmd::createData(const Data& _param) {
  Cmd _value;
  _value._type = _TypeData;
  _value._ptr = new Data(_param);
  return _value;
}

Cmd Cmd::fromBinary(BinaryReader& reader) {
  int _type;
  reader >> _type;
  if (_type==_TypePing) {
    return Cmd::createPing();
  } else if (_type==_TypeNewClient) {
    return Cmd::createNewClient(NewClientInfo::fromBinary(reader));
  } else if (_type==_TypeClientLost) {
    int v;
    reader >> v;
    return Cmd::createClientLost(v);
  } else if (_type==_TypeClientAccept) {
    int v;
    reader >> v;
    return Cmd::createClientAccept(v);
  } else if (_type==_TypeData) {
    return Cmd::createData(Data::fromBinary(reader));
  } else
    throw Exception("Cmd::fromBinary");
}
Cmd Cmd::fromSimpleData(const SimpleData& _data) {
  const SimpleVariant& _variant = _data.asVariant();
if (_variant.is("ping"))
    return Cmd::createPing();
  else if (_variant.is("newClient"))
    return Cmd::createNewClient(NewClientInfo::fromSimpleData(_variant.as("newClient")));
  else if (_variant.is("clientLost"))
    return Cmd::createClientLost(_variant.as("clientLost").asInt());
  else if (_variant.is("clientAccept"))
    return Cmd::createClientAccept(_variant.as("clientAccept").asInt());
  else if (_variant.is("data"))
    return Cmd::createData(Data::fromSimpleData(_variant.as("data")));
  else
    throw Exception("Cmd::fromSimpleData");
}

//----------------------------------

//------------- FdsArray ---------------
FdsArray::FdsArray() {
}
void FdsArray::toBinary(BinaryWriter& writer) const {
  writer << Size();
  for (int _i=0;_i<Size();_i++)
    writer << (*this)[_i];
}
SimpleData FdsArray::toSimpleData() const {
  SimpleArray _array;
  for (int _i=0;_i<Size();_i++)
    _array.Insert(SimpleData::createInt((*this)[_i]));
  return SimpleData::createArray(_array);
}
AnsiString FdsArray::toXML() const {
  AnsiString _xml = "<FdsArray>";
  for (int _i=0;_i<Size();_i++)
    _xml += "<int><![CDATA[" + AnsiString((*this)[_i]) + "]]></int>";
    _xml += "</FdsArray>";
    return _xml;
}
FdsArray::~FdsArray() {
}
FdsArray FdsArray::fromBinary(BinaryReader& reader) {
  FdsArray _value;
  int _no;
  reader >> _no;
  for (int _i=0;_i<_no;_i++) {
    int _v;
    reader >> _v;
    _value.Insert(_v);
  }
  return _value;
}
FdsArray FdsArray::fromSimpleData(const SimpleData& _data) {
  const SimpleArray& _array = _data.asArray();
  FdsArray _value;
  for (int _i=0;_i<_array.Size();_i++)
    _value.Insert(_array[_i].asInt());
  return _value;
}
//----------------------------------

//------------- Client ---------------
Client::Client(const AnsiString& _outbuf, const int& _id, const int& _fd) : outbuf(_outbuf), id(_id), fd(_fd) {
}
const AnsiString& Client::getOutbuf() const {
  return outbuf;
}
AnsiString& Client::getOutbuf() {
  return outbuf;
}
const int& Client::getId() const {
  return id;
}
int& Client::getId() {
  return id;
}
const int& Client::getFd() const {
  return fd;
}
int& Client::getFd() {
  return fd;
}
void Client::toBinary(BinaryWriter& writer) const {
  writer << outbuf;
  writer << id;
  writer << fd;
}
SimpleData Client::toSimpleData() const {
  SimpleRecord _record;
  _record.add("outbuf", SimpleData::createString(outbuf));
  _record.add("id", SimpleData::createInt(id));
  _record.add("fd", SimpleData::createInt(fd));
  return SimpleData::createRecord(_record);
}
AnsiString Client::toXML() const {
  AnsiString _xml = "<Client>";
    _xml += "<outbuf><![CDATA[" + AnsiString(outbuf)+"]]></outbuf>";
    _xml += "<id><![CDATA[" + AnsiString(id)+"]]></id>";
    _xml += "<fd><![CDATA[" + AnsiString(fd)+"]]></fd>";
  _xml += "</Client>";
  return _xml;
}
Client::~Client() {
}
Client Client::fromBinary(BinaryReader& reader) {
  AnsiString _outbuf;
  reader >> _outbuf;
  int _id;
  reader >> _id;
  int _fd;
  reader >> _fd;
  return Client(_outbuf, _id, _fd);
}
Client Client::fromSimpleData(const SimpleData& _data) {
  const SimpleRecord& _record = _data.asRecord();
  return Client(_record["outbuf"].asString(), _record["id"].asInt(), _record["fd"].asInt());
}
//----------------------------------

//------------- ConnClientsArray ---------------
ConnClientsArray::ConnClientsArray() {
}
void ConnClientsArray::toBinary(BinaryWriter& writer) const {
  writer << Size();
  for (int _i=0;_i<Size();_i++)
    (*this)[_i].toBinary(writer);
}
SimpleData ConnClientsArray::toSimpleData() const {
  SimpleArray _array;
  for (int _i=0;_i<Size();_i++)
    _array.Insert((*this)[_i].toSimpleData());
  return SimpleData::createArray(_array);
}
AnsiString ConnClientsArray::toXML() const {
  AnsiString _xml = "<ConnClientsArray>";
  for (int _i=0;_i<Size();_i++)
    _xml += (*this)[_i].toXML();
    _xml += "</ConnClientsArray>";
    return _xml;
}
ConnClientsArray::~ConnClientsArray() {
}
ConnClientsArray ConnClientsArray::fromBinary(BinaryReader& reader) {
  ConnClientsArray _value;
  int _no;
  reader >> _no;
  for (int _i=0;_i<_no;_i++) {
    _value.Insert(Client::fromBinary(reader));
  }
  return _value;
}
ConnClientsArray ConnClientsArray::fromSimpleData(const SimpleData& _data) {
  const SimpleArray& _array = _data.asArray();
  ConnClientsArray _value;
  for (int _i=0;_i<_array.Size();_i++)
    _value.Insert(Client::fromSimpleData(_array[_i]));
  return _value;
}
//----------------------------------

//------------- ConnData ---------------
ConnData::ConnData(const ConnClientsArray& _tcpclients, const FdsArray& _listenfds, const int& _fd, const int& _sfd, const AnsiString& _inbuf, const AnsiString& _outbuf, const int& _lastread, const int& _lastwrite) : tcpclients(_tcpclients), listenfds(_listenfds), fd(_fd), sfd(_sfd), inbuf(_inbuf), outbuf(_outbuf), lastread(_lastread), lastwrite(_lastwrite) {
}
const ConnClientsArray& ConnData::getTcpclients() const {
  return tcpclients;
}
ConnClientsArray& ConnData::getTcpclients() {
  return tcpclients;
}
const FdsArray& ConnData::getListenfds() const {
  return listenfds;
}
FdsArray& ConnData::getListenfds() {
  return listenfds;
}
const int& ConnData::getFd() const {
  return fd;
}
int& ConnData::getFd() {
  return fd;
}
const int& ConnData::getSfd() const {
  return sfd;
}
int& ConnData::getSfd() {
  return sfd;
}
const AnsiString& ConnData::getInbuf() const {
  return inbuf;
}
AnsiString& ConnData::getInbuf() {
  return inbuf;
}
const AnsiString& ConnData::getOutbuf() const {
  return outbuf;
}
AnsiString& ConnData::getOutbuf() {
  return outbuf;
}
const int& ConnData::getLastread() const {
  return lastread;
}
int& ConnData::getLastread() {
  return lastread;
}
const int& ConnData::getLastwrite() const {
  return lastwrite;
}
int& ConnData::getLastwrite() {
  return lastwrite;
}
void ConnData::toBinary(BinaryWriter& writer) const {
  tcpclients.toBinary(writer);
  listenfds.toBinary(writer);
  writer << fd;
  writer << sfd;
  writer << inbuf;
  writer << outbuf;
  writer << lastread;
  writer << lastwrite;
}
SimpleData ConnData::toSimpleData() const {
  SimpleRecord _record;
  _record.add("tcpclients", tcpclients.toSimpleData());
  _record.add("listenfds", listenfds.toSimpleData());
  _record.add("fd", SimpleData::createInt(fd));
  _record.add("sfd", SimpleData::createInt(sfd));
  _record.add("inbuf", SimpleData::createString(inbuf));
  _record.add("outbuf", SimpleData::createString(outbuf));
  _record.add("lastread", SimpleData::createInt(lastread));
  _record.add("lastwrite", SimpleData::createInt(lastwrite));
  return SimpleData::createRecord(_record);
}
AnsiString ConnData::toXML() const {
  AnsiString _xml = "<ConnData>";
    _xml += "<tcpclients>" + tcpclients.toXML() + "</tcpclients>";
    _xml += "<listenfds>" + listenfds.toXML() + "</listenfds>";
    _xml += "<fd><![CDATA[" + AnsiString(fd)+"]]></fd>";
    _xml += "<sfd><![CDATA[" + AnsiString(sfd)+"]]></sfd>";
    _xml += "<inbuf><![CDATA[" + AnsiString(inbuf)+"]]></inbuf>";
    _xml += "<outbuf><![CDATA[" + AnsiString(outbuf)+"]]></outbuf>";
    _xml += "<lastread><![CDATA[" + AnsiString(lastread)+"]]></lastread>";
    _xml += "<lastwrite><![CDATA[" + AnsiString(lastwrite)+"]]></lastwrite>";
  _xml += "</ConnData>";
  return _xml;
}
ConnData::~ConnData() {
}
ConnData ConnData::fromBinary(BinaryReader& reader) {
  ConnClientsArray _tcpclients = ConnClientsArray::fromBinary(reader);
  FdsArray _listenfds = FdsArray::fromBinary(reader);
  int _fd;
  reader >> _fd;
  int _sfd;
  reader >> _sfd;
  AnsiString _inbuf;
  reader >> _inbuf;
  AnsiString _outbuf;
  reader >> _outbuf;
  int _lastread;
  reader >> _lastread;
  int _lastwrite;
  reader >> _lastwrite;
  return ConnData(_tcpclients, _listenfds, _fd, _sfd, _inbuf, _outbuf, _lastread, _lastwrite);
}
ConnData ConnData::fromSimpleData(const SimpleData& _data) {
  const SimpleRecord& _record = _data.asRecord();
  return ConnData(ConnClientsArray::fromSimpleData(_record["tcpclients"]), FdsArray::fromSimpleData(_record["listenfds"]), _record["fd"].asInt(), _record["sfd"].asInt(), _record["inbuf"].asString(), _record["outbuf"].asString(), _record["lastread"].asInt(), _record["lastwrite"].asInt());
}
//----------------------------------

