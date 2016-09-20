#include "ConfigReader.h"

std::map<AnsiString, AnsiString> ConfigObj::getGroup(const AnsiString& group) {
  Logger::log("Get group ["+group+"]");
  for(std::map<AnsiString, std::map<AnsiString, AnsiString> >::iterator it=mapa.begin();it!=mapa.end();it++) {
      Logger::log(group+" "+it->first+" "+AnsiString(it->second.size()));
    }
  if(mapa.find(group)!=mapa.end()) {
    Logger::log("Group found");
    mapa[group];
  }
  return std::map<AnsiString, AnsiString>();
}

AnsiString ConfigObj::getValue(const AnsiString& group, const AnsiString& key) {
  if(getGroup(group).find(key)!=getGroup(group).end()) {
    std::map<AnsiString,AnsiString> deb = getGroup(group);
    for(std::map<AnsiString,AnsiString>::iterator it=deb.begin();it!=deb.end();it++) {
      Logger::log(group+" "+it->first+" "+it->second);
    }
    return mapa[group][key];
  }
  return "";
}

void ConfigObj::addGroup(const AnsiString& group) {
  mapa[group] = std::map<AnsiString, AnsiString>();
}

void ConfigObj::addValue(const AnsiString& group, const AnsiString& key, const AnsiString& value) {
  if(mapa.find(group)==mapa.end())
    addGroup(group);
  mapa[group][key]=value;
  Logger::log("[ConfigReader] Added ["+group+"]["+key+"]="+value);
}


static void readGroup(const DynSet<AnsiString>& lines, int& line, ConfigObj& obj) {
  while(line<lines.Size() && lines[line].Pos("[")<=0)
    line++;
  if(line==lines.Size())
    return;
  AnsiString groupName = lines[line].SubString(2, lines[line].Length()-2);
  Logger::log("[ConfigReader] groupName = " + groupName);
  line++;
  while(line<lines.Size() && lines[line].Pos("[")<=0) {
    int eqx = lines[line].Pos("=");
    int ceq = lines[line].Pos("#");
    if(eqx>0 && ceq!=1) {
      AnsiString key = lines[line].SubString(1, eqx-1);
      AnsiString value = lines[line].SubString(eqx+1, lines[line].Length()-eqx);
      obj.addValue(groupName, key, value);
    }
    line++;
  }
}

ConfigObj ConfigReader::read(const AnsiString& path) {
  ConfigObj obj;
  DynSet<AnsiString> lines = ShellUtil::exec("cat "+path);
  if(lines.Size()==0)
    throw Exception("[ConfigReader] Config file not found");
  int line = 0;
  while(line<lines.Size()) {
    readGroup(lines, line, obj);
  }
  return obj;
}
