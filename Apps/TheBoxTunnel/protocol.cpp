#include "AnsiString.h"
#include "DynSet.h"
#include "protocol.h"
#include "data/AppData.h"
#include "net.h"

#include <stdlib.h>
#include <stdio.h>

#define LOG_ERR 1
#define LOG_INFO 2
#define LOG_DEBUG 3

static int logLevel = LOG_DEBUG;

static void log(int kind, const AnsiString& msg) {
  if (kind>logLevel)
    return ;
  fprintf(stderr, "%d: Protocol: %s\n", time(NULL), msg.c_str());
  fflush(stderr);
}

static Exception Err(const AnsiString& msg) {
  throw Exception(msg);
}

static int min(int a, int b) {
  return (a<b) ? a : b;
}

static AnsiString mk1(int v) {
  unsigned char c = (unsigned char) (v % 256);
  return AnsiString((const char*) &c, 1);
}

static AnsiString mk2(int v) {
  unsigned char buf[2];
  buf[0] = (unsigned char) (v % 256);
  buf[1] = (unsigned char) (v / 256);
  return AnsiString((const char*) buf, 2);
}

static int extractCount(const unsigned char* buf) {
  return buf[0] + 256 * buf[1];
}

static int countRead(const AnsiString& inbuf) {
  int l = inbuf.Length();
  if (l<3)
    return 3 - l;
  const unsigned char* buf = (const unsigned char*) inbuf.c_str();
  int count = extractCount(buf);
  int crc = buf[2];
  if (crc!=(unsigned char) (6782387 * (count) % 255))
    throw Err("bad crc in count ");
  if (l>=3+count)
    throw Err("in protocol problem");
  return min(3+count-l, READBUF);
}

static int findTcpClient(int id, const DynSet<Client> &clients) {
  for (int i=0;i<clients.Size();i++)
    if (clients[i].getId()==id)
        return i;
  return -1;
}

void Protocol::reset(ConnData& connData) {
  DynSet<Client>& tcpclients = connData.getTcpclients();
  connData.getInbuf() = "";
  connData.getOutbuf() = "";
  while (connData.getTcpclients().Size()>0) {
    Net::doClose(tcpclients[0].getFd());
    tcpclients.Delete(0);
  }
  Net::doClose(connData.getFd());
}

DynSet<Cmd> Parser::parse(AnsiString& inbuf) {
  DynSet<Cmd> cmds;
  int l = inbuf.Length();
  const unsigned char* buf = (const unsigned char*)inbuf.c_str();
  int ix = 0;
  for (;;) {
    if (ix+3>l)
      break;
    int count = extractCount(buf + ix);
    int crc = buf[ix + 2];
    if (crc!=(unsigned char)(6782387 * (count) % 255))
      throw Err("bad crc in parser");
    if (ix+3+count>l)
      break;
    SimpleData s = SimpleData::fromString(inbuf.SubString(4+ix, 3+count)).asValue();
    cmds.Insert(Cmd::fromSimpleData(s));
    ix += 3+count;
  }
  inbuf = inbuf.SubString(1+ix, l-ix);
  return cmds;
}

AnsiString Protocol::mkCmd(Cmd cmd) {
  AnsiString buf = cmd.toSimpleData().toString();
  return mk2(buf.Length()) +  mk1(6782387 * (buf.Length()) % 255) + buf;
}

void Protocol::work(ConnData& connData, fd_set& readfds, fd_set& writefds, const DynSet<int>& tcpports, const AnsiString& boxHost, int boxPort) {
  DynSet<Client>& tcpclients = connData.getTcpclients();
  for (int i=0;i<connData.getListenfds().Size();i++) {
    if (connData.getListenfds()[i]!=-1 && FD_ISSET(connData.getListenfds()[i], &readfds)) {
      AnsiString ip;
      int nfd = Net::doAccept(connData.getListenfds()[i], ip);
      if (nfd<=0) {
        log(LOG_INFO, "accept client failed");
      }
      else {
        log(LOG_INFO, "local client from " + ip + " port " + tcpports[i] + " using " + nfd);
        tcpclients.Insert(Client(AnsiString(), nfd, nfd));
        connData.getOutbuf() += Protocol::mkCmd(Cmd::createNewClient(NewClientInfo(nfd, tcpports[i])));
      }
    }
  }

  for (int i=0;i<connData.getTcpclients().Size();i++) {
    Client& c = connData.getTcpclients()[i];
    if (c.getFd()!=-1 && FD_ISSET(c.getFd(), &writefds)) {
      if (Net::doWrite(c.getFd(), c.getOutbuf())<0) {
        log(LOG_INFO, "Close local connection, id: " + AnsiString(c.getId()));
        connData.getOutbuf() += Protocol::mkCmd(Cmd::createClientLost(c.getId()));
        Net::doClose(c.getFd());
        connData.getTcpclients().Delete(i--);
      }
    }
  }

  for (int i=0;i<connData.getTcpclients().Size();i++) {
    Client& c = connData.getTcpclients()[i];
    if (c.getFd()!=-1 && FD_ISSET(c.getFd(), &readfds)) {
      AnsiString inbuf = Net::doRead(c.getFd());
      if (inbuf.Length()>0) {
          connData.getOutbuf() += Protocol::mkCmd(Cmd::createData(Data(c.getId(), inbuf)));
      } else {
        log(LOG_INFO, "Close local connection, id: " + AnsiString(c.getId()));
        connData.getOutbuf() += Protocol::mkCmd(Cmd::createClientLost(c.getId()));
        Net::doClose(c.getFd());
        connData.getTcpclients().Delete(i--);
      }
    }
  }

  if (connData.getFd()!=-1 && connData.getOutbuf().Length()>0 && FD_ISSET(connData.getFd(), &writefds)) {
    if (connData.getOutbuf().Length()>0) {
      const char* buf = connData.getOutbuf().c_str();
      int l = connData.getOutbuf().Length();
      int err = send(connData.getFd(), buf, l, 0);
      if (err<=0) {
        log(LOG_ERR, "Send Error! Restart... ");
        reset(connData);
      }
      else {
        connData.getLastwrite() = time(NULL);
        connData.getOutbuf() = connData.getOutbuf().SubString(1 + err, l - err);
      }
    }
  }

  if (connData.getFd()!=-1 && FD_ISSET(connData.getFd(), &readfds)) {
    char buf[READBUF];
    int l = countRead(connData.getInbuf());
    int err = recv(connData.getFd(), buf, l, 0);
    if (err<=0) {
      log(LOG_ERR, "Recv Error! Restart... ");
      reset(connData);
    } else {
      connData.getLastread() = time(NULL);
      connData.getInbuf() += AnsiString(buf, err);
      try {
        DynSet<Cmd> cmds = Parser::parse(connData.getInbuf());
        Protocol::execCmds(connData.getTcpclients(), cmds, connData.getOutbuf(), boxHost, boxPort);
        }
      catch (...) {
        log(LOG_ERR, "Protocol error!");
        reset(connData);
      }
    }
  }

  if (time(NULL)-connData.getLastwrite()>WRITETIMEOUT && connData.getOutbuf().Length()==0) {
    connData.getOutbuf() += Protocol::mkCmd(Cmd::createPing());
    log(LOG_DEBUG, "Send ping");
  }
    
  if (time(NULL)-connData.getLastread()>READTIMEOUT) {
    log(LOG_ERR, "Timeout! Restart..." + AnsiString(connData.getLastread()));
    reset(connData);
  }
}

void Protocol::execCmds(DynSet<Client>& tcpclients, DynSet<Cmd> cmds, AnsiString& outbuf, const AnsiString& boxHost, int boxPort) {
  log(LOG_INFO, "Receive " + AnsiString(cmds.Size()) + " cmds");
  for (int i=0;i<cmds.Size();i++) {
    const Cmd& cmd = cmds[i];
    if (cmd.isPing()) {
      log(LOG_DEBUG, "Recv ping" );
    } else
    if (cmd.isNewClient()) {
      NewClientInfo info = cmd.asNewClient();
      int connport = info.getConnport();
      int id = info.getId();
      int nfd = Net::mkConnect(boxHost, boxPort);
      if(nfd<=0) {
        log(LOG_INFO, "Connect to local client failed, connport: " + AnsiString(connport));
        outbuf += mkCmd(Cmd::createClientLost(id));
      }
      else {
        log(LOG_INFO, "!Connect to local client ok, fd: " + AnsiString(nfd) + " host: " + boxHost +" connport: " + AnsiString(boxPort));
        outbuf += mkCmd(Cmd::createClientAccept(id));
        tcpclients.Insert(Client(AnsiString(), id, nfd));
      }
    } else
    if (cmd.isClientLost()) {
      int id = cmd.asClientLost();
      log(LOG_INFO, "Close local connection, id: " + AnsiString(id));
      int x = findTcpClient(id, tcpclients);
      if(x != -1) {
        Net::doClose(tcpclients[x].getFd());
        tcpclients.Delete(x);
      }
    } else
    if (cmd.isClientAccept()) {
      int id = cmd.asClientAccept();
      log(LOG_INFO, "Remote client accepted, id" + AnsiString(id));
    } else
    if (cmd.isData()) {
      Data data = cmd.asData();
      int x = findTcpClient(data.getId(), tcpclients);
      if( x ==-1 )
        outbuf += mkCmd(Cmd::createClientLost(data.getId()));
      else
        tcpclients[x].getOutbuf() += data.getSource();
    } else {
      log(LOG_ERR, "Unknown Cmd!");
    }
  }
}
