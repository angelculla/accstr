#include "accstr.h"



accstr global_txt(10);           // this one uses dynamic memory. global scope



void foo() {
  char txt[11];
  accstr local_txt(txt,10);      // this one uses external array in stack (txt). Note that txt has one extra byte for the ending zero
  accstr local_dm_txt(10);       // this other uses dynamic memory

  Serial.print(F("global_txt+=\"12\" > "));
  if (global_txt+="12") {
    Serial.print(global_txt.txt);
    Serial.println(F(" - OK"));
  }
  else {
    Serial.print(global_txt.txt);
    Serial.println(F(" - Overflow!!!"));
  }

  Serial.print(F("local_txt=\"0123456789\" > "));
  if (local_txt="0123456789") {
    Serial.print(local_txt.txt);
    Serial.println(F(" - OK"));
  }
  else {
    Serial.print(local_txt.txt);
    Serial.println(F(" - Overflow!!!"));
  }

  Serial.print(F("local_dm_txt=\"Hello world\" > "));
  if (local_dm_txt="Hello world") {
    Serial.print(local_dm_txt.txt);
    Serial.println(F(" - OK"));
  }
  else {
    Serial.print(local_dm_txt.txt);
    Serial.println(F(" - Overflow!!!"));
  }

  if (local_dm_txt=="Hello world") Serial.println(F("local_dm_txt is equal to \"Hello world\""));
  else Serial.println(F("local_dm_txt is different to \"Hello world\""));

  Serial.print("Free heap size: ");
  Serial.println(ESP.getFreeHeap());
  Serial.println();
}



void setup() {
  Serial.begin(115200);
  Serial.println(F("\nACCSTR example program\n"));
}



void loop() {
  foo();
  delay(5000);
}