#ifndef PORTS_H_INCLUDED
#define PORTS_H_INCLUDED


#include "../types.h"


Byte in(short port);
void out(short port, Byte data);

void out32(short port, int data);
int  in32(short port);


#include "ports.c"

#endif //PORTS_H_INCLUDED