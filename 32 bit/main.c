void kernel();

void start()
{
	kernel();

	for(;;);
}


#include "types.h"
#include "extends.h"
#include "output stream/output stream.h"
#include "devices/screen/text screen.h"


#include "devices/keyboard/keyboard.h"
#include "devices/time/time.h"
#include "devices/audio/PC speaker/PC speaker.h"


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

/*
void test_memory()
{
	print_character('H');
	print("Hi");
	print(0x500);

	for(;;);

	Byte* memory1 = create_memory(10);
	Byte* memory2 = create_memory(10);

	destroy_memory(memory1);
	destroy_memory(memory2);

	create_memory(123);

	print_memory();
}*/

#include "devices/ports.h"


unsigned int read_PCI_config (Byte bus, Byte device, Byte function, Byte register_number)
{
	unsigned int device_address =
		  0b10000000000000000000000000000000 //enable bit
		| (bus << 16)
		| (device << 11)
		| (function << 8)
		| (register_number << 2)
		& 0b11111100;

	out32(0xcf8, device_address);
	return in32(0xcfc);
}


void kernel()
{
	Text_Screen   *default_screen        = get_default_text_screen();
	Output_Stream *default_screen_stream = get_default_text_screen_output_stream();

	initialize_text_screen (default_screen, 0x0B8000, 80, 25);
	initialize_output_stream (default_screen_stream, default_screen, write_byte_in_text_screen);

	unsigned int i;
	unsigned int j;

	for(i=0; i<256; ++i)
	{
		for(j=0; j<32; ++j)
		{
			unsigned int config = read_PCI_config(i, j, 0, 0);

			if(config != 0xffffffff)
			{
				print_null_terminated_byte_array("bus:");
				print_unsigned_integer(i);

				print_null_terminated_byte_array(" device:");
				print_unsigned_integer(j);

				print_null_terminated_byte_array(" PCI vendor:");
				print_unsigned_integer(config & 0xffff);

				print_null_terminated_byte_array(" PCI device:");
				print_unsigned_integer(config >> 16);

				unsigned int config2 = read_PCI_config(i, j, 0, 2);

				print_null_terminated_byte_array(" PCI class:");
				print_unsigned_integer(config >> 24);

				print_null_terminated_byte_array(" PCI subclass:");
				print_unsigned_integer(config >> 16 && 0xff);

				print_byte(',');
			}
		}
	}
}