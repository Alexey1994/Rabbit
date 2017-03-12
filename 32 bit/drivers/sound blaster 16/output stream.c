#include "output stream.h"
#include "../ports.h"

#include "../../display output.h"


void reset_sound_blaster()
{
	int i;

	out(0x226, 1);

	for(i=0; i<3000; ++i);

	out(226, 0);

	while(in(0x22E) & 0x01000000b)
	{

	}

	//while(in(0x22A) != 0xAA)
	for(;;)
	{
		Byte t=in(0x22A);

		if(t==0xAA)
			break;

		//print_integer((int)t);
	}
}


void play_byte(Byte byte)
{

	//while(!(in(0x22C) & 0));

	out(0x22C, byte);
}