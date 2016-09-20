#include "Utils.h"

int main(int argc, const char* argv[]) {
  PGLibraryLoader loader("./postgresql/lib/libpq.dll");
  SDBConn pbxDb(loader);
  SDBConn nilDb(loader);
  const AnsiString timeout = "10";
  
  printf("Łączene z bazą...\n");
  while(true) {
    try {
      pbxDb.Connect("10.0.0.5", "postgres", "pbx", "");
      nilDb.Connect("10.0.0.5", "postgres", "nil", "");
      printf("Połączenie ok\n");
      go()
    } catch (Exception e) {
      throw e;
    }
    Sleep(1);
  }
}
