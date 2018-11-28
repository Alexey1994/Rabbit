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


Output* get_default_text_screen_output()
{
	static Output text_screen_output;

	return &text_screen_output;
}


void write_byte_in_text_screen(Text_Screen *screen, Byte byte)
{
	if(byte == '\n')
	{
		++screen->y_coord;
		screen->x_coord = 0;
	}
	else
	{
		screen->address[ (screen->x_max * screen->y_coord + screen->x_coord)*2 ] = byte;
		++screen->x_coord;
	}

	if(screen->x_coord == screen->x_max)
	{
		screen->x_coord = 0;
		++screen->y_coord;
	}

	if(screen->y_coord == screen->y_max)
	{
		int i;

		//shift up
		for(i=0; i < screen->x_max * (screen->y_max-1) * 2; i+=2)
			screen->address[i] = screen->address[i + screen->x_max*2];

		//clear last line
		for(i=screen->x_max * (screen->y_max-1) * 2; i < screen->x_max * screen->y_max * 2; i+=2)
			screen->address[i] = 0;

		--screen->y_coord;
	}
}

/*
void print_byte(Byte byte)
{
	Output *screen_output = get_default_text_screen_output();
	screen_output->write_byte(screen_output->source, byte);
}


void print_null_terminated_byte_array(Byte *byte_array)
{
	write_null_terminated_byte_array_in_output (get_default_text_screen_output(), byte_array);
}


void print_unsigned_integer(unsigned int number)
{
	write_unsigned_integer_in_output (get_default_text_screen_output(), number);
}*/