
#include "common.h"
#include <cstdio>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

int main(int argc, const char* argv[]) {
  if (argc<=4) {
    printf("%s connect_ip connect_port box_host box_port\n", argv[0]);
    return 1;
  }
  
  try {
    int connport = atoi(argv[2]);
    DynSet<int> tcpports; 
    Net::networkInit();
    go(argv[1], connport, tcpports, argv[3], atoi(argv[4]));
  } catch (const Exception& e) {
    fprintf(stderr, "%s\n", ("E: " + e.Message).c_str());
  } catch (...) {
    fprintf(stderr, "%s\n", "E ??");
  }
}
