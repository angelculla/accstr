/***************************************************************************
accstr is a class to manage C strings (STRINGZ) safely

You can use dynamic memory or an external char array to store the string
depending of the constructor called. In any case the max size of the string
is fixed to avoid heap fragmentation. If you need strings of variable size
you should use the standard Arduino class "String".

The methods cpy(), cat() and catc() works safely to avoid range overflows,
they cuts the result string if the max size is reached. False is returned
in that case. There are versions of cpy() and cat() methods to use PROGMEM
source strings (see Arduino macro F)

The size indicated in the constructor is the util number of chars that you
can to store in the string. One extra byte is reserved for the ending zero,
take care of this if you use an external array.  

Despite using STRINGZ the actual size is managed by an internal variable
instead the ending zero. This allow to have zeros inside the string and so
you can use this class to store non text data buffers. In any case the
ending zero is allways there.

The property "text" is the char pointer to the string
****************************************************************************/


#include <Arduino.h>



class accstr {
  private:
    char *txt;
    uint16_t tmaxsize;
    uint16_t tsize;
    bool useheap;
  public:
    accstr(uint16_t sz);                         // uses heap to store the string
    accstr(char *p, uint16_t sz);                // uses external char* array (avoids dynamic memory)
    ~accstr();
    char* text();                                // returns pointer to the string
    uint16_t maxsize();                          // returns the max size of the string
    uint16_t size();                             // returns the actual size of the string
    bool cpy(char *src);                         // copies one string 
    bool cpy(const __FlashStringHelper *src);    // copies from PROGMEM
    bool cat(char *src);                         // adds a string
    bool cat(const __FlashStringHelper *src);    // adds from PROGMEM
    bool catc(char c);                           // adds a single char
    void clear();                                // clears the string (no heap is released if used)
    bool operator=(char *src);
    bool operator=(const __FlashStringHelper *src);
    bool operator+=(char *src);
    bool operator+=(const __FlashStringHelper *src);
    bool operator==(char *src);
    bool operator==(const __FlashStringHelper *src);
};
