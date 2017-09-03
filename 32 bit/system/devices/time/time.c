Byte get_time_seconds()
{
	out(0x70, 0);
	Byte seconds = in(0x71);

	return (seconds & 0x0F) + ((seconds / 16) * 10);
}

Byte get_time_minutes()
{
	out(0x70, 2);
	Byte minutes = in(0x71);

	return (minutes & 0x0F) + ((minutes / 16) * 10);
}

Byte get_time_hours()
{
	out(0x70, 4);
	Byte hours = in(0x71);

	return ( (hours & 0x0F) + (((hours & 0x70) / 16) * 10) ) | (hours & 0x80);
}


void print_date()
{
	print_unsigned_integer( get_time_hours() );
	print_byte(' ');
	print_byte(':');
	print_byte(' ');
	print_unsigned_integer( get_time_minutes() );
	print_byte(' ');
	print_byte(':');
	print_byte(' ');
	print_unsigned_integer( get_time_seconds() );

	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
	print_byte(' ');
}