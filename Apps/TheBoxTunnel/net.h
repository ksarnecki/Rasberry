#ifndef NET_H
#define NET_H

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

#include "data/AppData.h"

class Net {
  public:
  	static void networkInit();
    static void doClose(int& fd);
    static AnsiString doRead(int fd);
    static int doWrite(int fd, AnsiString& outbuf);
    static int mkConnect(const AnsiString& host, int port);
    static int mkListen(int port, bool localhost);
    static int doAccept(int fd, AnsiString& remoteIp);
    static int doSelect(ConnData& connData, fd_set& readfds, fd_set& writefds);
};

#endif
