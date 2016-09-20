#include "MoviesMenager.h"

static bool cmp(const MediaInfoObj& obj1, const MediaInfoObj& obj2) {
  bool t1 = obj1.getVideoInfoObj().getCodec() == obj2.getVideoInfoObj().getCodec();
  bool t2 = obj1.getAudioInfoObj().getFormat() == obj2.getAudioInfoObj().getFormat();
  return t1 && t2;
}

void MoviesMenager::loadMovies(AnsiString configFile, AnsiString moviesDir) {
  try { 
  //load basic movies info
  FILE* inputFile;
  if((inputFile = fopen(configFile.c_str(), "rb")) == NULL) {
    Logger::err("Cannot open file: " + configFile);
  }
  
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, inputFile)) != -1) {
    AnsiString configLine = line;
    int hashPos = configLine.Pos("#");
    if(hashPos<=0 || hashPos==configLine.Length())
      Logger::err("Bad file syntax: " + configLine);
    AnsiString moviePath = moviesDir+"/"+configLine.SubString(1, hashPos-1);
    try {
      printf("prob: %s, path: %s\n", configLine.SubString(hashPos+1, configLine.Length()-hashPos-1).c_str(), moviePath.c_str());
      int movieWeigth = std::stoi(configLine.SubString(hashPos+1, configLine.Length()-hashPos).c_str());
      //test movie
      FILE* fd = NULL;
      if((fd = fopen(moviePath.c_str(), "rb")) == NULL) {
        Logger::log("File not found " + moviePath);
        continue;
      } else {
        movies.Insert(Movie(moviePath, movieWeigth, MediaInfoUtil::getInfo(moviePath)));
        sumWeights += movieWeigth; 
        fclose(fd);
      }
    } catch(std::exception e) {
      Logger::err("Bad file syntax: " + configLine); 
    }
  }
  //validating infos
  if (movies.Size() == 0)
	  Logger::err("Empty movies list!");
  AnsiString info = movies[0].getMediaInfoObj().toJSON();
  for (int i = 1; i < movies.Size(); i++) {
          Logger::log("Load movie: " + movies[i].getMediaInfoObj().toJSON());
	  if (!cmp(movies[i].getMediaInfoObj(), (movies[0].getMediaInfoObj()))) {
		  Logger::err("Movie " + movies[i].getPath() + "bad format!\n" + movies[i].getMediaInfoObj().toJSON() + "\n not match\n" + movies[0].getMediaInfoObj().toJSON());
	  }
  }
  srand(time(NULL));
  fclose(inputFile);
  free(line);
  ShellUtil::exec("/usr/bin/python /home/player/cpp/RasberryPiUtils/Apps/Displayer/Displayer.py");
  } catch(Exception e) {
    ShellUtil::exec("/usr/bin/python /home/player/cpp/RasberryPiUtils/Apps/Displayer/Displayer.py");
    throw e;
  }
}

AnsiString MoviesMenager::getNext() {
  printf("[getNext] Start\n");
  while(1==1) {
    int r = rand()%sumWeights;
    printf("total %d rand %d\n", sumWeights, r);
    int i=-1;
    do {
      r-= movies[++i].getWeight();
    } while(r>0);
    if(prev == i && movies.Size() > 1)
      continue;
    prev = i;
    printf("stop at %d\n", i);
    printf("[getNext] %s\n", movies[i].getPath().c_str());
    return movies[i].getPath();
  }
}
