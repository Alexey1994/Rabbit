void kernel();

void start()
{
	kernel();

	for(;;);
}


#include "types.h"
#include "extends.h"
#include "output/output.h"
#include "system/devices/screen/text screen.h"


#include "system/devices/keyboard/keyboard.h"
#include "system/devices/time/time.h"
#include "system/devices/audio/PC speaker/PC speaker.h"

#include "system/interfaces/PCI/PCI.h"


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

//#include "devices/ports.h"


void kernel()
{
	Text_Screen   *default_screen        = get_default_text_screen();
	Output        *default_screen_output = get_default_text_screen_output();

	initialize_text_screen (default_screen, 0x0B8000, 80, 25);
	initialize_output (default_screen_output, default_screen, write_byte_in_text_screen);

	PCI_Device device;

	unsigned int current_bus;
	unsigned int current_device;

	device.ID.function = 0;

	for(current_bus = 0; current_bus < 256; ++current_bus)
	{
		for(current_device = 0; current_device < 32; ++current_device)
		{
			unsigned int config = read_from_PCI(current_bus, current_device, 0, 0);

			if(config != 0xffffffff)
			{
				device.ID.bus    = current_bus;
				device.ID.device = current_device;

				device.vendor = config & 0xffff;
				device.device = config >> 16;

				config = read_from_PCI(device.ID.bus, device.ID.device, 0, 2);
				device.class = config >> 24;
				device.subclass = (config >> 16) & 0xff;
				device.revision = config & 0xff;

				print_PCI_device(&device);
				print_null_terminated_byte_array("\n");
			}
		}
	}
}