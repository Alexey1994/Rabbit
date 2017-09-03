#include "output stream.h"
#include "../ports.h"

#include "../../display output.h"


void reset_sound_blaster()
{
	int i;

	out_8(0x226, 1);

	for(i=0; i<3000; ++i);

	out_8(0x226, 0);

	while(in_8(0x22E) & 0x01000000b)
	{

	}

	//while(in(0x22A) != 0xAA)
	for(;;)
	{
		Byte t=in_8(0x22A);

		if(t==0xAA)
			break;

		//print_integer((int)t);
	}
}


void play_byte(Byte byte)
{

	//while(!(in_16(0x22C) & 0));

	out_8(0x22C, byte);
}