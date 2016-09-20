
#include <stdlib.h>
#include <stdio.h>

#include "AnsiString.h"
#include "DynSet.h"
#include "data/AppData.h"
#include "protocol.h"
#include "net.h"

#define LOG_ERR 1
#define LOG_INFO 2
#define LOG_DEBUG 3

static int logLevel = LOG_DEBUG;

static void log(int kind, const AnsiString& msg) {
  if (kind>logLevel)
    return ;
  fprintf(stderr, "%d: Common: %s\n", time(NULL), msg.c_str());
  fflush(stderr);
}

static Exception Err(const AnsiString& msg) {
  log(LOG_ERR, msg);
  throw Exception(msg);
}

static void doSleep(int v) {
#ifndef _WIN32
  sleep(v);
#else
  Sleep(v*1000);
#endif
}

void go(const AnsiString& connhost, int hostport, const DynSet<int>& tcpports, const AnsiString& boxHost, int boxPort) {
  ConnData connData(ConnClientsArray(), FdsArray(), -1, -1, AnsiString(), AnsiString(), time(NULL), time(NULL));
  
  if (connhost.Length()==0)
    connData.getSfd() = Net::mkListen(hostport, false);

  for (int i=0;i<tcpports.Size();i++) {
    int nfd = Net::mkListen(tcpports[i], true);
    if (nfd==-1)
      throw Err("mkListen");
    connData.getListenfds().Insert(nfd);
  }

  for (;;) {
    while (connData.getFd()==-1) {
      if (connhost.Length()==0) {
        AnsiString ip;
        log(LOG_INFO, "waiting for client");
        connData.getFd() = Net::doAccept(connData.getSfd(), ip);
        if (connData.getFd()<=0) {
          log(LOG_INFO, "accept failed");
          doSleep(1);
          connData.getFd() = -1;
        } else
          log(LOG_INFO, "client from " + ip + " using " + connData.getFd());
      } else {
        log(LOG_INFO, "connecting to " + connhost + ":" + hostport + "...");
        connData.getFd() = Net::mkConnect(connhost, hostport);
        if (connData.getFd()<=0) {
          throw Err("main mkConnect");
        } else {
          log(LOG_INFO, "connect ok" + AnsiString(connData.getFd()));
        }
      }
      connData.getLastread() = time(NULL);
    }

    fd_set readfds;
    fd_set writefds;
    Net::doSelect(connData, readfds, writefds);
    Protocol::work(connData, readfds, writefds, tcpports, boxHost, boxPort);
  }
}
