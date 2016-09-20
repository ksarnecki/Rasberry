#include "ShellUtil.h"

bool ShellUtil::CmdExist(const AnsiString& cmd) {
  return exec("command -v " + cmd).Size()>0;
}

bool ShellUtil::ServiceExist(const AnsiString& service) {
  return exec("ls /etc/init.d | grep " + service).Size()>0;
}

void ShellUtil::reboot() {
  exec("sudo reboot");
}

DynSet<AnsiString> ShellUtil::exec(const AnsiString& cmd) {
  DynSet<AnsiString> d;
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) 
    return d;
  char buffer[128];
  std::string result = "";
  while (!feof(pipe) && cmd.Pos("&") <= 0) {
    if (fgets(buffer, 128, pipe) != NULL)
      result += buffer;
  }
  std::istringstream f(result);
  std::string line;    
  while (std::getline(f, line)) {
     d.Insert(line);
  }
  pclose(pipe);
  return d;
}

