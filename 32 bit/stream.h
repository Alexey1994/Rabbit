#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED


#include "types.h"


void put_integer(int num, void(*put_byte)(Byte byte));


#include "stream.c"

#endif //STREAM_H_INCLUDED