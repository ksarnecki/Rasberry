
#ifndef _WIN32

#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#else
#include <winsock2.h>
#include <time.h>

typedef int socklen_t;

#endif

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
  fprintf(stderr, "%d: Net: %s\n", time(NULL), msg.c_str());
  fflush(stderr);
}

static Exception Err(const AnsiString& msg) {
  log(LOG_ERR, msg);
  throw Exception(msg);
}

void Net::doClose(int& fd) {
#ifndef _WIN32
  close(fd);
#else
  closesocket(fd);
#endif
  fd = -1;
}

static int max(int a, int b) {
  return (a>b) ? a : b;
}

void Net::networkInit() {
  #ifndef _WIN32
  #else
    WSADATA WSAData;
    if (WSAStartup (MAKEWORD(2,2), &WSAData) != 0)
      throw Exception("WSAStartup"); 
  #endif
}

int Net::mkConnect(const AnsiString& host, int port) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd==-1)
    return -1;
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(host.c_str());

  if (connect(fd, (const sockaddr*) &addr, sizeof(addr))<0) {
    doClose(fd);
    return -1;
  }
  return fd;
}

int Net::mkListen(int port, bool localhost) {
  int s;
  if ((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    return -1;
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  if(localhost) 
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  
  else
    server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  int optval = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*) &optval, sizeof optval);
  if (bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR) {
    doClose(s);
    return -1;
  }
  listen(s, 3);
  return s;
}

int Net::doAccept(int fd, AnsiString& remoteIp) {
  struct sockaddr_in client;
  socklen_t c = sizeof(struct sockaddr_in);
  int nfd = accept(fd, (struct sockaddr *)&client, &c);
  if (nfd!=-1)
    remoteIp = AnsiString(inet_ntoa(client.sin_addr));
  return nfd;
}

AnsiString Net::doRead(int fd) {
  char ibuf[READBUF];
  int count = recv(fd, ibuf, READBUF, 0);
  if (count>0)
    return AnsiString(ibuf, count);
  return AnsiString();
}

int Net::doWrite(int fd, AnsiString& outbuf) {
  int l = outbuf.Length();
  int err = send(fd, outbuf.c_str(), outbuf.Length(), 0);
  if (err>0)
    outbuf = outbuf.SubString(1+err, l-err);
  return err;
}

int Net::doSelect(ConnData& connData, fd_set& readfds, fd_set& writefds) {
  DynSet<Client>& tcpclients = connData.getTcpclients();
  int maxfd = connData.getFd();
  FD_ZERO(&readfds);
  FD_ZERO(&writefds);
  FD_SET(connData.getFd(), &readfds);
  if (connData.getOutbuf().Length()>0)
    FD_SET(connData.getFd(), &writefds);

  for (int i=0;i<connData.getTcpclients().Size();i++) {
    maxfd = max(maxfd, connData.getTcpclients()[i].getFd());
    FD_SET(connData.getTcpclients()[i].getFd(), &readfds);
    if (tcpclients[i].getOutbuf().Length()>0)
      FD_SET(connData.getTcpclients()[i].getFd(), &writefds);
  }

  for (int i=0;i<connData.getListenfds().Size();i++) {
    FD_SET(connData.getListenfds()[i], &readfds);
    maxfd = max(maxfd, connData.getListenfds()[i]);
  }

  struct timeval to;
  to.tv_sec = SELECTTIMEOUT;
  to.tv_usec = 0;
  int err = select(maxfd + 1, &readfds, &writefds, NULL, &to);
  if (err<0) 
    throw Err("select");
  log(LOG_DEBUG, "select bye");
  return err;
}
