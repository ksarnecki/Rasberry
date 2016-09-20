#ifndef MOVIES_LOADER_H
#define MOVIES_LOADER_H

#include "DynSet.h"
#include "AnsiString.h"

#include "MediaInfoUtil.h"

#include "data/AppData.h"

#include "Logger.h"

class MoviesMenager {
  private:
    DynSet<Movie> movies;
 
    int sumWeights = 0;
    int prev = -1;

  public:
    void loadMovies(AnsiString configFile, AnsiString moviesDir);
    AnsiString getNext();
};
#endif
