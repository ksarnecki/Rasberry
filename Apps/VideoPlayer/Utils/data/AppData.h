#ifndef _APPDATA_GEN_H_
#define _APPDATA_GEN_H_
#include "DynSet.h"
#include <stdio.h>
#include <stdlib.h>
//------------- string ---------------
#include "AnsiString.h"
//----------------------------------

//------------- int ---------------
//----------------------------------

//------------- MediaInfoObj ---------------
#include "MediaInfoObj.h"
//----------------------------------

//------------- Movie ---------------
class Movie {
  AnsiString path;
  int weight;
  MediaInfoObj mediaInfoObj;
public:
  Movie(const AnsiString&, const int&, const MediaInfoObj&);
  virtual const AnsiString& getPath() const;
  virtual const int& getWeight() const;
  virtual const MediaInfoObj& getMediaInfoObj() const;
  virtual AnsiString& getPath();
  virtual int& getWeight();
  virtual MediaInfoObj& getMediaInfoObj();

  virtual AnsiString toJSON() const;
  static Movie fromJSON(AnsiString);

  virtual ~Movie();

};
//----------------------------------

#endif
