#ifndef SHELL_UTIL
#define SHELL_UTIL

#include "AnsiString.h"
#include "DynSet.h"

#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <memory>

#include "Logger.h"

class ShellUtil {
  public:
    static DynSet<AnsiString> exec(const AnsiString&);
    static bool CmdExist(const AnsiString&);
    static void reboot();
    static bool ServiceExist(const AnsiString&);
};

#endif