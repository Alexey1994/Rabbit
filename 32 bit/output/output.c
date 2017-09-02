void initialize_output(Output *output, Byte *source, void (*write_byte)(Byte *source, Byte byte))
{
	output->source     = source;
	output->write_byte = write_byte;
}


void deinitialize_output(Output *output)
{

}


void write_null_terminated_byte_array_in_output(Output *output, Byte *array)
{
	while(*array)
	{
		output->write_byte(output->source, *array);
		++array;
	}
}


void write_unsigned_integer_in_output(Output *output, unsigned int number)
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
		output->write_byte(output->source, number / right_selector % 10 + '0');
		right_selector /= 10;
	}
	while(right_selector);
}