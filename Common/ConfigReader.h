#ifndef CONFIG_READER
#define CONFIG_READER

#include "ShellUtil.h"
#include "Exception.h"
#include "Logger.h"

#include <map>

class ConfigObj {
  private:
    std::map<AnsiString, std::map<AnsiString, AnsiString> > mapa;
  public:
    std::map<AnsiString, AnsiString> getGroup(const AnsiString&);
    AnsiString getValue(const AnsiString&, const AnsiString&);    
    void addGroup(const AnsiString&);
    void addValue(const AnsiString&, const AnsiString&, const AnsiString&);
};

class ConfigReader {
  public:
    static ConfigObj read(const AnsiString&);
};

#endif