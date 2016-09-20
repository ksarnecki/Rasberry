#ifndef _MEDIAINFOOBJ_GEN_H_
#define _MEDIAINFOOBJ_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- VideoInfoObj ---------------
class VideoInfoObj {
  AnsiString codec;
  AnsiString width;
  AnsiString height;
  AnsiString profile;
  AnsiString fps;
public:
  VideoInfoObj(const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&, const AnsiString&);
  virtual const AnsiString& getCodec() const;
  virtual const AnsiString& getWidth() const;
  virtual const AnsiString& getHeight() const;
  virtual const AnsiString& getProfile() const;
  virtual const AnsiString& getFps() const;
  virtual AnsiString& getCodec();
  virtual AnsiString& getWidth();
  virtual AnsiString& getHeight();
  virtual AnsiString& getProfile();
  virtual AnsiString& getFps();

  virtual AnsiString toJSON() const;
  static VideoInfoObj fromJSON(AnsiString);

  virtual ~VideoInfoObj();

};
//----------------------------------

//------------- AudioInfoObj ---------------
class AudioInfoObj {
  AnsiString format;
  AnsiString samplerate;
  AnsiString bitspersample;
public:
  AudioInfoObj(const AnsiString&, const AnsiString&, const AnsiString&);
  virtual const AnsiString& getFormat() const;
  virtual const AnsiString& getSamplerate() const;
  virtual const AnsiString& getBitspersample() const;
  virtual AnsiString& getFormat();
  virtual AnsiString& getSamplerate();
  virtual AnsiString& getBitspersample();

  virtual AnsiString toJSON() const;
  static AudioInfoObj fromJSON(AnsiString);

  virtual ~AudioInfoObj();

};
//----------------------------------

//------------- MediaInfoObj ---------------
class MediaInfoObj {
  VideoInfoObj videoInfoObj;
  AudioInfoObj audioInfoObj;
public:
  MediaInfoObj(const VideoInfoObj&, const AudioInfoObj&);
  virtual const VideoInfoObj& getVideoInfoObj() const;
  virtual const AudioInfoObj& getAudioInfoObj() const;
  virtual VideoInfoObj& getVideoInfoObj();
  virtual AudioInfoObj& getAudioInfoObj();

  virtual AnsiString toJSON() const;
  static MediaInfoObj fromJSON(AnsiString);

  virtual ~MediaInfoObj();

};
//----------------------------------

#endif
