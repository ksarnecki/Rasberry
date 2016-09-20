#include "Logger.h"

void Logger::write(AnsiString file, AnsiString str) {
  FILE *fp;
  fp = fopen(file.c_str(), "a+");
  fprintf(fp, (str+"\n").c_str());
  fclose(fp);
}

static AnsiString ts() {
  return ShellUtil::exec("echo $(date)")[0];
}

void Logger::log(AnsiString msg) {
  write(LOG, "[LOG]["+ts()+"] " + msg);
}

void Logger::err(AnsiString err) {
  write(LOG, "[ERR]["+ts()+"] " + err);
  throw Exception(err);
}


