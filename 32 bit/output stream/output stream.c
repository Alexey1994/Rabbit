void initialize_output_stream(Output_Stream *stream, Byte *source, void (*write_byte)(Byte *source, Byte byte))
{
	stream->source     = source;
	stream->write_byte = write_byte;
}


void deinitialize_output_stream(Output_Stream *stream)
{

}


void write_null_terminated_byte_array_in_output_stream(Output_Stream *stream, Byte *array)
{
	while(*array)
	{
		stream->write_byte(stream->source, *array);
		++array;
	}
}


void write_unsigned_integer_in_output_stream(Output_Stream *stream, unsigned int number)
{
	unsigned int number_copy    = number;
	int right_selector          = 1;

	for(;;)
	{
		number_copy /= 10;

		if(!number_copy)
			break;

		right_selector *= 10;
	}

	do
	{
		stream->write_byte(stream->source, number / right_selector % 10 + '0');
		right_selector /= 10;
	}
	while(right_selector);
}