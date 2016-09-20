#ifndef _PROTOCOL_H
#define _PROTOCOL_H 1

#include "AnsiString.h"
#include "DynSet.h"
#include "data/AppData.h"
#include "net.h"

#define READTIMEOUT 8
#define WRITETIMEOUT (READTIMEOUT/2)
#define SELECTTIMEOUT (WRITETIMEOUT/2)

#define READBUF 2048

class Parser {
  public:
    static DynSet<Cmd> parse(AnsiString& inbuf);
};

class Protocol {
  private:
    static void reset(ConnData& connData);
    static void execCmds(DynSet<Client>& tcpclients, DynSet<Cmd> cmds, AnsiString& outubf, const AnsiString& boxHost, int boxPort);
    static AnsiString mkCmd(Cmd cmd);
    
  public:
    static void work(ConnData& connData, fd_set& readfds, fd_set& writefds, const DynSet<int>& tcpports, const AnsiString& boxHost, int boxPort);
};
#endif
