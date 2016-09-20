
#ifndef COMMON
#define COMMON 1

#include "AnsiString.h"
#include "DynSet.h" 
#include "net.h"

void go(const AnsiString& connhost, int connport, const DynSet<int>& tcpports, const AnsiString& boxHost, int boxPort);

#endif
