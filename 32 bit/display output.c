#include "display output.h"
#include "stream.h"


void print_character(Character c)
{
	int i;

	static int     screen_x = 0;
	unsigned char *screen   = (unsigned char*)0x0B8000;

	screen[screen_x] = c;
	screen_x += 2;

	if(screen_x > 4000)
	{
		for(i=4000; i>=160; i -= 2)
			screen[i - 160] = screen[i];

		for(i=4000 - 160; i<4000; i += 2)
			screen[i] = ' ';

		//screen_x = 4000 - 160;
		screen_x = 0;
	}
}


void print_integer(int num)
{
	put_integer(num, print_character);
	print_character(' ');
}


void print(Character *array)
{
	while(*array)
	{
		print_character(*array);
		++array;
	}
}