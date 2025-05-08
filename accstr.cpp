#include <accstr.h>



accstr::accstr(char *p, uint16_t sz) {
  txt=p;
  useheap=false;
  tsize=0;
  txt[0]=0;
  tmaxsize=sz;
}



accstr::accstr(uint16_t sz) {
  txt=(char*)malloc(sz+1);
  useheap=true;
  tsize=0;
  txt[0]=0;
  tmaxsize=sz;
}



accstr::~accstr() {
  if (useheap) free(txt);
}



uint16_t accstr::maxsize() {
  return tmaxsize;
}



uint16_t accstr::size() {
  return tsize;
}



bool accstr::cpy(char *src) {
  uint16_t i;
  bool res;

  tsize=strlen(src);
  if (tsize>tmaxsize) {
    tsize=tmaxsize;
    res=false;
  }
  else {
    res=true;
  }
  for (i=0;i<tsize;i++) txt[i]=src[i];
  txt[tsize]=0;
  return res;  
}



bool accstr::cat(char *src) {
  uint16_t i,sz;
  bool res;

  sz=strlen(src);
  if ((tsize+sz)>tmaxsize) {
    sz=tmaxsize-tsize;
    res=false;
  }
  else {
    res=true;
  }
  for (i=0;i<sz;i++) txt[tsize++]=src[i];
  txt[tsize]=0;
  return res;  
}



bool accstr::cpy(const __FlashStringHelper *src) {
  uint16_t i;
  bool res;

  tsize=strlen_P((const char*)src);
  if (tsize>tmaxsize) {
    tsize=tmaxsize;
    res=false;
  }
  else {
    res=true;
  }
  for (i=0;i<tsize;i++) txt[i]=pgm_read_byte_near((const char*)src+i);
  txt[tsize]=0;
  return res;  
}



bool accstr::cat(const __FlashStringHelper *src) {
  uint16_t i,sz;
  bool res;

  sz=strlen_P((const char*)src);
  if ((tsize+sz)>tmaxsize) {
    sz=tmaxsize-tsize;
    res=false;
  }
  else {
    res=true;
  }
  for (i=0;i<sz;i++) txt[tsize++]=pgm_read_byte_near((const char*)src+i);
  txt[tsize]=0;
  return res;  
}



bool accstr::catc(char c) {
  if (tsize>=tmaxsize) return false;
  txt[tsize++]=c;
  txt[tsize]=0;
  return true;
}



void accstr::clear() {
  tsize=0;
  txt[0]=0;
}



bool accstr::operator=(char *src) {
  return cpy(src);
}



bool accstr::operator+=(char *src) {
  return cat(src);
}



bool accstr::operator==(char *src) {
  if (strcmp(txt,src)==0) return true;
  else return false;
}



bool accstr::operator=(const __FlashStringHelper *src) {
  return cpy(src);
}



bool accstr::operator+=(const __FlashStringHelper *src) {
  return cat(src);
}



bool accstr::operator==(const __FlashStringHelper *src) {
  if (strcmp(txt,(const char*)src)==0) return true;
  else return false;
}



