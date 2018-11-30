#include "system.h"


function N_32 kmain();

procedure start_system()
{
    kmain();
}


#include "output/output.h"
#include "system/text screen/text screen.h"
#include "system/interrupts/interrupts.h"
#include "system/network/ethernet/AMD PCNET/AMD PCNET.h"


void find_devices(PCI_Device *device)
{
    if(device->device == 0x2000 && device->vendor == 0x1022)
    {
        write_null_terminated_byte_array(get_default_text_screen_output(), "AMD PCNET finded\n");
        configure_AMD_PCNET(device);
    }
    else if(device->device == 0x7000 && device->vendor == 0x8086)
    {
        //print_null_terminated_byte_array("VGA controller finded\n");
        //configure_VGA(device);
    }
}


function N_32 kmain()
{
	Text_Screen   *default_screen        = get_default_text_screen();
	Output        *default_screen_output = get_default_text_screen_output();

	initialize_text_screen (default_screen, 0x0B8000, 80, 25);
	initialize_output (default_screen_output, default_screen, &write_byte_in_text_screen);

    //find_PCI_devices(&find_devices);

    initialize_interrupts();

	return 0;
}