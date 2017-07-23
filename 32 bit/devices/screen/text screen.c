void initialize_text_screen(Text_Screen *text_screen, Byte *address, unsigned int x_max, unsigned int y_max)
{
	text_screen->address = address;
	text_screen->x_coord = 0;
	text_screen->y_coord = 0;
	text_screen->x_max   = x_max;
	text_screen->y_max   = y_max;
}


Text_Screen* get_default_text_screen()
{
	static Text_Screen default_screen;

	return &default_screen;
}


Output_Stream* get_default_text_screen_output_stream()
{
	static Output_Stream text_screen_output_stream;

	return &text_screen_output_stream;
}


void write_byte_in_text_screen(Text_Screen *screen, Byte byte)
{
	screen->address[ (screen->x_max * screen->y_coord + screen->x_coord)*2 ] = byte;

	++screen->x_coord;
}


void print_byte(Byte byte)
{
	Output_Stream *screen_stream = get_default_text_screen_output_stream();
	screen_stream->write_byte(screen_stream->source, byte);
}


void print_null_terminated_byte_array(Byte *byte_array)
{
	write_null_terminated_byte_array_in_output_stream (get_default_text_screen_output_stream(), byte_array);
}


void print_unsigned_integer(unsigned int number)
{
	write_unsigned_integer_in_output_stream (get_default_text_screen_output_stream(), number);
}