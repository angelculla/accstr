#include <accstr.h>



accstr::accstr(char *p, uint16_t sz) {
  pbuf=p;
  useheap=false;
  tsize=0;
  pbuf[0]=0;
  tmaxsize=sz;
}



accstr::accstr(uint16_t sz) {
  pbuf=(char*)malloc(sz+1);
  useheap=true;
  tsize=0;
  pbuf[0]=0;
  tmaxsize=sz;
}



accstr::~accstr() {
  if (useheap) free(pbuf);
}



char* accstr::text() {
  return pbuf;
}



uint16_t accstr::maxsize() {
  return tmaxsize;
}



uint16_t accstr::size() {
  return tsize;
}



void accstr::setsize(uint16_t sz) {
  if (sz>tmaxsize) sz=tmaxsize;
  tsize=sz;
  pbuf[tsize]=0;
}



void accstr::setpbuf(char *p, uint16_t sz) {
  if (useheap) {
    free(pbuf);
    useheap=false;
  }
  pbuf=p;
  tsize=0;
  pbuf[0]=0;
  tmaxsize=sz;
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
  for (i=0;i<tsize;i++) pbuf[i]=src[i];
  pbuf[tsize]=0;
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
  for (i=0;i<tsize;i++) pbuf[i]=pgm_read_byte_near((const char*)src+i);
  pbuf[tsize]=0;
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
  for (i=0;i<sz;i++) pbuf[tsize++]=src[i];
  pbuf[tsize]=0;
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
  for (i=0;i<sz;i++) pbuf[tsize++]=pgm_read_byte_near((const char*)src+i);
  pbuf[tsize]=0;
  return res;  
}



bool accstr::catc(char c) {
  if (tsize>=tmaxsize) return false;
  pbuf[tsize++]=c;
  pbuf[tsize]=0;
  return true;
}



bool accstr::cpyint(int32_t val) {
  char src[31];
  int i;

  i=snprintf(src,30,"%d",val);
  if (i<0) return false;
  return cpy(src);
}



bool accstr::catint(int32_t val) {
  char src[31];
  int i;

  i=snprintf(src,30,"%d",val);
  if (i<0) return false;
  return cat(src);
}



bool accstr::cpyfmt(char *fmt, ...) {
  char src[101];
  va_list ap;

  va_start(ap,fmt);
  vsnprintf(src,100,fmt,ap);
  va_end(ap);
  return cpy(src);
}



bool accstr::catfmt(char *fmt, ...) {
  char src[101];
  va_list ap;

  va_start(ap,fmt);
  vsnprintf(src,100,fmt,ap);
  va_end(ap);
  return cat(src);
}



void accstr::clear() {
  tsize=0;
  pbuf[0]=0;
}



bool accstr::operator=(char *src) {
  return cpy(src);
}



bool accstr::operator=(const __FlashStringHelper *src) {
  return cpy(src);
}



bool accstr::operator=(int32_t val) {
  return cpyint(val);
}



bool accstr::operator+=(char *src) {
  return cat(src);
}



bool accstr::operator+=(const __FlashStringHelper *src) {
  return cat(src);
}



bool accstr::operator+=(int32_t val) {
  return catint(val);
}



bool accstr::operator==(char *src) {
  if (strcmp(pbuf,src)==0) return true;
  else return false;
}



bool accstr::operator==(const __FlashStringHelper *src) {
  if (strcmp(pbuf,(const char*)src)==0) return true;
  else return false;
}


