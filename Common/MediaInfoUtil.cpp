 #include "MediaInfoUtil.h"
 
 int getKV(const AnsiString& line, AnsiString& key, AnsiString& value) {
  int ix = line.Pos(":");
  if(ix > 0) {
    key = line.SubString(1, ix-1).Trim();
    value = line.SubString(ix+1, line.Length()-ix).Trim();
  }
  return ix;
 }
 
 MediaInfoObj MediaInfoUtil::getInfo(const AnsiString& path) {
   DynSet<AnsiString> lines = ShellUtil::exec("mediainfo " + path);
   bool audio_lines = true;
   AnsiString v_codec = "";
   AnsiString width = "";
   AnsiString height = "";
   AnsiString profile = "";
   AnsiString fps = "";
   AnsiString a_codec = "";
   AnsiString samplerate = "";
   AnsiString bitspersample = "";
   for(int i=0;i<lines.Size();i++) {
     AnsiString key,value;
     if(getKV(lines[i], key, value) > 0) {
       if(audio_lines) {
         if(key == "Format") {
           v_codec = value;
         } else if (key == "Width") {
           width = value;
         } else if (key == "Height") {
           height = value;
         } else if (key.Pos("Profile") > 0) {
           profile += value + ";";
         } else if (key == "Frame rate") {
           fps += value;
         }
       } else {
         if(key == "Format") {
           a_codec = value;
         } else if (key == "Sampling rate") {
           samplerate = value;
         } else if (key == "Height") {
           height = value;
         } else if (key.Pos("Bit rate") > 0) {
           bitspersample += value + ";";
         }
       }
     } else {
       if(lines[i].Pos("Video")>0)
         audio_lines = false;
     }
   }
   VideoInfoObj vObj = VideoInfoObj(v_codec, width, height, profile, fps);
   AudioInfoObj aObj = AudioInfoObj(a_codec, samplerate, bitspersample);
   MediaInfoObj mObj = MediaInfoObj(vObj, aObj);
   return mObj; 
 }