#include "Utils.h"

static inline AnsiString clean(const AnsiString& str) {
  return str.UpperCase().Trim();
}
static AnsiString conv(const AnsiString& name, const AnsiString& surname, const AnsiString& job_number) {
  return clean(name) + "#" + clean(surname) + "#" + clean(job_number);
}

void go() {
  std::string number;
  while(getline(std::cin, number)) {
    
  }
}