#ifndef OUTPUT_STREAM_H_INCLUDED
#define OUTPUT_STREAM_H_INCLUDED


typedef struct
{
	Byte  *source;
	void (*write_byte)(Byte *source, Byte byte);
}
Output_Stream;


void initialize_output_stream   (Output_Stream *stream, Byte *source, void (*write_byte)(Byte *source, Byte byte));
void deinitialize_output_stream (Output_Stream *stream);

void write_null_terminated_byte_array_in_output_stream (Output_Stream *stream, Byte *array);
void write_decimal_integer_number_in_output_stream     (Output_Stream *stream, int number);


#include "output stream.c"

#endif //OUTPUT_STREAM_H_INCLUDED