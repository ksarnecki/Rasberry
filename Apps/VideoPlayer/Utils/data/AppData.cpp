
#include "AppData.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- string ---------------
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- MediaInfoObj ---------------
//----------------------------------

//------------- Movie ---------------
Movie::Movie(const AnsiString& _path, const int& _weight, const MediaInfoObj& _mediaInfoObj) : path(_path), weight(_weight), mediaInfoObj(_mediaInfoObj) {
}
const AnsiString& Movie::getPath() const {
  return path;
}
AnsiString& Movie::getPath() {
  return path;
}
const int& Movie::getWeight() const {
  return weight;
}
int& Movie::getWeight() {
  return weight;
}
const MediaInfoObj& Movie::getMediaInfoObj() const {
  return mediaInfoObj;
}
MediaInfoObj& Movie::getMediaInfoObj() {
  return mediaInfoObj;
}
AnsiString Movie::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"path\":";
    _json += "\"" + JSONEscape::encode(path) + "\"";
    _json += ",";
    _json += "\"weight\":";
    _json += AnsiString(weight);
    _json += ",";
    _json += "\"mediaInfoObj\":";
    _json += mediaInfoObj.toJSON();
  _json += "}";
  return _json.get();
}
Movie Movie::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("Movie::fromJSON");
    int start = ix;
    bool inString = false;
    int bracketLevel = 0;
    while (ix<=s.Length()) {
      if (s[ix]=='\\')
        ix+=2;
      else if (s[ix]=='"')
        inString = !inString;
      else if (!inString && s[ix]=='[')
        bracketLevel++;
      else if (!inString && s[ix]=='{')
        bracketLevel++;
      else if (!inString && s[ix]==']')
        bracketLevel--;
      else if (!inString && s[ix]=='}')
        bracketLevel--;
      if (bracketLevel<=0 && !inString && ((ix<=s.Length() && s[ix]==',') || ix==s.Length())) {
        if (i<3) {
          if (ix-start-1<=0)
            throw Exception("Movie::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return Movie((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), atoi(arr[1].c_str()), MediaInfoObj::fromJSON(arr[2]));
}
Movie::~Movie() {
}
//----------------------------------

