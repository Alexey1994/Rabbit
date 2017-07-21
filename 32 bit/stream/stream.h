#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED


#include "../types.h"


typedef struct
{
	Byte  *source;
	Byte (*read_byte)(Byte *source);
	void (*write_byte)(Byte *source, Byte byte);
}
InputStream;


typedef struct
{
	Byte  *source;
	Byte (*read_byte)(Byte *source);
	void (*write_byte)(Byte *source, Byte byte);
}
OutputStream;


Stream* create_input_stream();
Stream* create_output_stream();


#include "stream.c"

#endif //STREAM_H_INCLUDED