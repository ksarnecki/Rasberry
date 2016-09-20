#ifndef MEDIAINFO_UTIL_H
#define MEDIAINFO_UTIL_H

#include "data/MediaInfoObj.h"

#include "ShellUtil.h"

class MediaInfoUtil {
  public:
    static MediaInfoObj getInfo(const AnsiString&);
};

#endif
