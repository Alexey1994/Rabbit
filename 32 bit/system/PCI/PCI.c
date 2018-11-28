/*
   | bits 31-24  | bits 23-16  |  bits 15-8    | bits 7-0             |
-----------------------------------------------------------------------
00 | Device ID                 |  Vendor ID                           |
   --------------------------------------------------------------------
04 | Status                    |  Command                             |
   --------------------------------------------------------------------
08 | Class code  | Subclass    |  Prog IF      | Revision ID          |
   --------------------------------------------------------------------
0C | BIST        | Header type | Latency Timer | Cache Line Size      |
   --------------------------------------------------------------------
10 | Base address #0 (BAR0)                                           |
   --------------------------------------------------------------------
14 | Base address #1 (BAR1)                                           |
   --------------------------------------------------------------------
18 | Base address #2 (BAR2)                                           |
   --------------------------------------------------------------------
1C | Base address #3 (BAR3)                                           |
   --------------------------------------------------------------------
20 | Base address #4 (BAR4)                                           |
   --------------------------------------------------------------------
24 | Base address #5 (BAR5)                                           |
   --------------------------------------------------------------------
28 | Cardbus CIS Pointer                                              |
   --------------------------------------------------------------------
2C | Subsystem ID              | Subsystem Vendor ID                  |
   --------------------------------------------------------------------
30 | Expansion ROM base address                                       |
   --------------------------------------------------------------------
34 | Reserved                                  | Capabilities Pointer |
   --------------------------------------------------------------------
38 | Reserved                                                         |
   --------------------------------------------------------------------
3C | Max latency | Min Grant   | Interrupt PIN | Interrupt Line       |
   -------------------------------------------------------------------- 
*/


function N_32 read_from_PCI_device_config (PCI_Device *device, Byte address)
{
    N_32 device_address;

    device_address =
        0b10000000000000000000000000000000 //enable bit
        | (device->ID.bus << 16)
        | (device->ID.device << 11)
        | (device->ID.function_number << 8)
        | address;

    out_32(0xcf8, device_address);
    return in_32(0xcfc);
}


procedure write_in_PCI_device_config (PCI_Device *device, Byte address, N_32 data)
{
    N_32 device_address;

    device_address =
        0b10000000000000000000000000000000 //enable bit
        | (device->ID.bus << 16)
        | (device->ID.device << 11)
        | (device->ID.function_number << 8)
        | address;

    out_32(0xcf8, device_address);
    out_32(0xcfc, data);
}


procedure print_PCI_device (Output *output, PCI_Device *device)
{
    write_null_terminated_byte_array(output, "bus:");
    write_N_32(output, device->ID.bus);

    write_null_terminated_byte_array(output, " device:");
    write_N_32(output, device->ID.device);

    write_null_terminated_byte_array(output, " PCI vendor:");
    write_hex_N_16(output, device->vendor);

    write_null_terminated_byte_array(output, " PCI device:");
    write_hex_N_16(output, device->device);

    write_null_terminated_byte_array(output, " revision ID:");
    write_N_32(output, device->revision);

    write_null_terminated_byte_array(output, " class:");
    write_N_32(output, device->class);

    //write_null_terminated_byte_array(output, " subclass:");
    //write_N_32(output, device->subclass);
}


procedure find_PCI_devices (procedure (*on_finded)(PCI_Device *device))
{
    PCI_Device device;

    N_32 current_bus;
    N_32 current_device;

    for(current_bus = 0; current_bus < 256; ++current_bus)
    //for(device.ID.bus = 0; device.ID.bus < 256; ++device.ID.bus)
    {
        //for(current_device = 0; current_device < 32; ++current_device)
        for(device.ID.device = 0; device.ID.device < 32; ++device.ID.device)
        {
            for(device.ID.function_number = 0; device.ID.function_number < 8; ++device.ID.function_number)
            {
                device.ID.bus    = current_bus;
                //device.ID.device = current_device;

                N_32 config = read_from_PCI_device_config(&device, 0);

                if(config != 0xffffffff)
                {
                    device.vendor = config & 0xffff;
                    device.device = config >> 16;

                    config = read_from_PCI_device_config(&device, 0x08);
                    device.class = config >> 24;
                    device.subclass = (config >> 16) & 0xff;
                    device.revision = config & 0xff;

                    cycle(0, 6, 1)
                      device.BAR[i] = read_from_PCI_device_config(&device, 0x10 + i * 4) & 0b11111111111111111111111111110000;

                      /*if(device.BAR[i] & 1)
                        write_null_terminated_byte_array(get_default_text_screen_output(), "memory i/o ");
                      else
                        write_null_terminated_byte_array(get_default_text_screen_output(), "i/o ");

                      write_hex_N_32(get_default_text_screen_output(), device.BAR[i]);
                      write_byte(get_default_text_screen_output(), '\n');*/
                    end_cycle

                    on_finded(&device);
                }
            }
        }
    }
}