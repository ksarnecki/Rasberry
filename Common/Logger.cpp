#include "Logger.h"

void Logger::write(AnsiString file, AnsiString str) {
  FILE *fp;
  fp = fopen(file.c_str(), "a+");
  fprintf(fp, (str+"\n").c_str());
  fclose(fp);
}

void Logger::log(AnsiString msg) {
  write(LOG, "[LOG]" + msg);
}

void Logger::err(AnsiString err) {
	write(LOG, "[ERR]" + err);
	throw Exception(err);
}


