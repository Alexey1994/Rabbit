#ifndef PORTS_H_INCLUDED
#define PORTS_H_INCLUDED

#include "../../../types.h"


Byte           in_8   (short port);
void           out_8  (short port, Byte data);

unsigned short in_16  (short port);
void           out_16 (short port, unsigned short data);

void           out32  (short port, int data);
int            in32   (short port);


#include "ports.c"

#endif //PORTS_H_INCLUDED