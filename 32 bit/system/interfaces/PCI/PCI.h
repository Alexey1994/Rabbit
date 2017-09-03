#ifndef PCI_H_INCLUDED
#define PCI_H_INCLUDED


#include "../../interfaces/ports/ports.h"


typedef struct
{
	struct
	{
		Byte bus;
		Byte device;
		Byte function;
	}
	ID;

	unsigned short vendor;
	unsigned short device;
	Byte           revision;
	Byte           class;
	Byte           subclass;
}
PCI_Device;


//unsigned int read_from_PCI       (Byte bus, Byte device, Byte function, Byte register_number);
unsigned int read_from_PCI_device (PCI_Device *device, Byte register_number);
void         write_in_PCI_device (PCI_Device *device, Byte register_number, unsigned int data);
void         print_PCI_device    (PCI_Device *device);
void         find_PCI_devices    (void(*on_finded)(PCI_Device *device));


#include "PCI.c"

#endif //PCI_H_INCLUDED