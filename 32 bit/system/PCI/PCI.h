#ifndef SYSTEM_PCI_H_INCLUDED
#define SYSTEM_PCI_H_INCLUDED


#include "../IO/IO.h"


typedef struct
{
    struct
    {
        Byte bus;
        Byte device;
        Byte function_number;
    }
    ID;

    N_16 vendor;
    N_16 device;
    Byte revision;
    Byte class;
    Byte subclass;

    N_32 BAR[6];
}
PCI_Device;


function  N_32 read_from_PCI_device_config (PCI_Device *device, Byte address);
procedure      write_in_PCI_device_config  (PCI_Device *device, Byte address, N_32 data);
procedure      print_PCI_device            (Output *output, PCI_Device *device);
procedure      find_PCI_devices            (procedure (*on_finded)(PCI_Device *device));


#include "PCI.c"

#endif //SYSTEM_PCI_H_INCLUDED