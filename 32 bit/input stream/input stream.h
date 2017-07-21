#ifndef INPUT_STREAM_H_INCLUDED
#define INPUT_STREAM_H_INCLUDED


typedef struct 
{
	Byte  *source;
	Byte (*read_byte)(Byte *source);
}
Input_Stream;


Input_Stream* create_input_stream  (Byte *source, Byte (*read_byte)(Byte *source));
void          destroy_input_stream (Input_Stream *stream);


#include "input stream.c"

#endif //INPUT_STREAM_H_INCLUDED