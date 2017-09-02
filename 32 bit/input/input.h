#ifndef INPUT_H_INCLUDED
#define INPUT_INCLUDED


typedef struct 
{
	Byte  *source;
	Byte (*read_byte)(Byte *source);
}
Input;


Input* create_input  (Byte *source, Byte (*read_byte)(Byte *source));
void   destroy_input (Input *stream);


#include "input.c"

#endif //INPUT_H_INCLUDED