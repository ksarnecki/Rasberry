#include <cstdio>
#include <stdlib.h>
#include "common.h"

#ifdef _WIN32
#include <winsock2.h>
#endif


int main(int argc, const char* argv[]) {
  if (argc<=2) {
    printf("%s conn_port listen_port [listen_port]\n", argv[0]);
    return 1;
  }

  try {
    int connport = atoi(argv[1]);
    DynSet<int> tcpports;
    
    for(int i=2;i<argc;i++) {
      tcpports.Insert(atoi(argv[i]));
    }

    Net::networkInit();
   
    go("", connport, tcpports, "", 0);
  } catch (const Exception& e) {
    fprintf(stderr, "%s\n", ("E: " + e.Message).c_str());
  } catch (...) {
    fprintf(stderr, "%s\n", "E ??");
  }
}

