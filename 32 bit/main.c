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

#include "system/devices/network/ethernet/AMD PCNET/AMD PCNET.h"


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


void configure_VGA(PCI_Device *device)
{
	unsigned int device_config;
	unsigned int base_address;
/*
	device_config = read_from_PCI_device(device, 4);

	device_config = (device_config & 0xffff0000)
		| 0b00000101;

	write_in_PCI_device(device, 4, device_config);*/
/*
	write_in_PCI_device(device, 4, 0x00000004);
	write_in_PCI_device(device, 4, 0x00035f00);
*/
	base_address = read_from_PCI_device(device, 4);

	print_null_terminated_byte_array("\nbase address0 ");
	print_unsigned_integer(base_address);

	base_address = read_from_PCI_device(device, 5);

	print_null_terminated_byte_array("\nbase address1 ");
	print_unsigned_integer(base_address);

	base_address = read_from_PCI_device(device, 6);

	print_null_terminated_byte_array("\nbase address2 ");
	print_unsigned_integer(base_address);

	base_address = read_from_PCI_device(device, 7);

	print_null_terminated_byte_array("\nbase address3 ");
	print_unsigned_integer(base_address);

	base_address = read_from_PCI_device(device, 8);

	print_null_terminated_byte_array("\nbase address4 ");
	print_unsigned_integer(base_address);

	base_address = read_from_PCI_device(device, 9);

	print_null_terminated_byte_array("\nbase address5 ");
	print_unsigned_integer(base_address);

	print_null_terminated_byte_array("\n");
}


void find_devices(PCI_Device *device)
{
	if(device->device == 0x2000 && device->vendor == 0x1022)
	{
		print_null_terminated_byte_array("AMD PCNET finded\n");
		configure_AMD_PCNET(device);
	}
	else if(device->device == 0x7000 && device->vendor == 0x8086)
	{
		print_null_terminated_byte_array("VGA controller finded\n");
		//configure_VGA(device);
	}
	else
		;//configure_AMD_PCNET(device);

	//print_PCI_device(device);
}


void kernel()
{
	Text_Screen   *default_screen        = get_default_text_screen();
	Output        *default_screen_output = get_default_text_screen_output();

	initialize_text_screen (default_screen, 0x0B8000, 80, 25);
	initialize_output (default_screen_output, default_screen, write_byte_in_text_screen);

	find_PCI_devices(find_devices);
}