
#include "MediaInfoObj.h"
#include "Exception.h"
#include "StringBuffer.h"
#include "JSONUtil.h"
//------------- string ---------------
//----------------------------------

//------------- VideoInfoObj ---------------
VideoInfoObj::VideoInfoObj(const AnsiString& _codec, const AnsiString& _width, const AnsiString& _height, const AnsiString& _profile, const AnsiString& _fps) : codec(_codec), width(_width), height(_height), profile(_profile), fps(_fps) {
}
const AnsiString& VideoInfoObj::getCodec() const {
  return codec;
}
AnsiString& VideoInfoObj::getCodec() {
  return codec;
}
const AnsiString& VideoInfoObj::getWidth() const {
  return width;
}
AnsiString& VideoInfoObj::getWidth() {
  return width;
}
const AnsiString& VideoInfoObj::getHeight() const {
  return height;
}
AnsiString& VideoInfoObj::getHeight() {
  return height;
}
const AnsiString& VideoInfoObj::getProfile() const {
  return profile;
}
AnsiString& VideoInfoObj::getProfile() {
  return profile;
}
const AnsiString& VideoInfoObj::getFps() const {
  return fps;
}
AnsiString& VideoInfoObj::getFps() {
  return fps;
}
AnsiString VideoInfoObj::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"codec\":";
    _json += "\"" + JSONEscape::encode(codec) + "\"";
    _json += ",";
    _json += "\"width\":";
    _json += "\"" + JSONEscape::encode(width) + "\"";
    _json += ",";
    _json += "\"height\":";
    _json += "\"" + JSONEscape::encode(height) + "\"";
    _json += ",";
    _json += "\"profile\":";
    _json += "\"" + JSONEscape::encode(profile) + "\"";
    _json += ",";
    _json += "\"fps\":";
    _json += "\"" + JSONEscape::encode(fps) + "\"";
  _json += "}";
  return _json.get();
}
VideoInfoObj VideoInfoObj::fromJSON(AnsiString s) {
  AnsiString arr[5];
  int ix=1;
  for (int i=0;i<5;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("VideoInfoObj::fromJSON");
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
        if (i<5) {
          if (ix-start-1<=0)
            throw Exception("VideoInfoObj::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return VideoInfoObj((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), (arr[2].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))), (arr[3].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[3].SubString(2, arr[3].Length()-2))), (arr[4].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[4].SubString(2, arr[4].Length()-2))));
}
VideoInfoObj::~VideoInfoObj() {
}
//----------------------------------

//------------- AudioInfoObj ---------------
AudioInfoObj::AudioInfoObj(const AnsiString& _format, const AnsiString& _samplerate, const AnsiString& _bitspersample) : format(_format), samplerate(_samplerate), bitspersample(_bitspersample) {
}
const AnsiString& AudioInfoObj::getFormat() const {
  return format;
}
AnsiString& AudioInfoObj::getFormat() {
  return format;
}
const AnsiString& AudioInfoObj::getSamplerate() const {
  return samplerate;
}
AnsiString& AudioInfoObj::getSamplerate() {
  return samplerate;
}
const AnsiString& AudioInfoObj::getBitspersample() const {
  return bitspersample;
}
AnsiString& AudioInfoObj::getBitspersample() {
  return bitspersample;
}
AnsiString AudioInfoObj::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"format\":";
    _json += "\"" + JSONEscape::encode(format) + "\"";
    _json += ",";
    _json += "\"samplerate\":";
    _json += "\"" + JSONEscape::encode(samplerate) + "\"";
    _json += ",";
    _json += "\"bitspersample\":";
    _json += "\"" + JSONEscape::encode(bitspersample) + "\"";
  _json += "}";
  return _json.get();
}
AudioInfoObj AudioInfoObj::fromJSON(AnsiString s) {
  AnsiString arr[3];
  int ix=1;
  for (int i=0;i<3;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("AudioInfoObj::fromJSON");
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
            throw Exception("AudioInfoObj::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return AudioInfoObj((arr[0].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[0].SubString(2, arr[0].Length()-2))), (arr[1].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[1].SubString(2, arr[1].Length()-2))), (arr[2].Length()-2<0 ? throw Exception("String::FromJSON") : JSONEscape::decode(arr[2].SubString(2, arr[2].Length()-2))));
}
AudioInfoObj::~AudioInfoObj() {
}
//----------------------------------

//------------- MediaInfoObj ---------------
MediaInfoObj::MediaInfoObj(const VideoInfoObj& _videoInfoObj, const AudioInfoObj& _audioInfoObj) : videoInfoObj(_videoInfoObj), audioInfoObj(_audioInfoObj) {
}
const VideoInfoObj& MediaInfoObj::getVideoInfoObj() const {
  return videoInfoObj;
}
VideoInfoObj& MediaInfoObj::getVideoInfoObj() {
  return videoInfoObj;
}
const AudioInfoObj& MediaInfoObj::getAudioInfoObj() const {
  return audioInfoObj;
}
AudioInfoObj& MediaInfoObj::getAudioInfoObj() {
  return audioInfoObj;
}
AnsiString MediaInfoObj::toJSON() const {
  StringBuffer _json;
  _json += "{";
    _json += "\"videoInfoObj\":";
    _json += videoInfoObj.toJSON();
    _json += ",";
    _json += "\"audioInfoObj\":";
    _json += audioInfoObj.toJSON();
  _json += "}";
  return _json.get();
}
MediaInfoObj MediaInfoObj::fromJSON(AnsiString s) {
  AnsiString arr[2];
  int ix=1;
  for (int i=0;i<2;i++) {
    while (ix<=s.Length() && s[ix]!=':')
      ix++;
    if (ix>s.Length()) 
      throw Exception("MediaInfoObj::fromJSON");
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
        if (i<2) {
          if (ix-start-1<=0)
            throw Exception("MediaInfoObj::fromJSON");
          arr[i] = s.SubString(start+1, ix-start-1);
        }
        ix++;
        break;
      }
      ix++;
    }
  }
  return MediaInfoObj(VideoInfoObj::fromJSON(arr[0]), AudioInfoObj::fromJSON(arr[1]));
}
MediaInfoObj::~MediaInfoObj() {
}
//----------------------------------

