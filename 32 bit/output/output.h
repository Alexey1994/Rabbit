#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED


typedef struct
{
	Byte  *source;
	void (*write_byte)(Byte *source, Byte byte);
}
Output;


void initialize_output   (Output *output, Byte *source, void (*write_byte)(Byte *source, Byte byte));
void deinitialize_output (Output *output);

void write_null_terminated_byte_array_in_output (Output *output, Byte *array);
void write_unsigned_integer_in_output           (Output *output, unsigned int number);


#include "output.c"

#endif //OUTPUT_H_INCLUDED