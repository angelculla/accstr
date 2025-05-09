# accstr
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

The operators =, += and == are overloaded to easily assign, add and compare.
See more info in the comments in accstr.h
