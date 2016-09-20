#ifndef LOGGER
#define LOGGER

#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "AnsiString.h"
#include "DynSet.h"
#include "Exception.h"

#define LOG AnsiString("/var/log/rpi_logger.log")

class Logger {
  public:
    static void write(AnsiString, AnsiString);
    static void log(AnsiString);
	static void err(AnsiString);
};

#endif
