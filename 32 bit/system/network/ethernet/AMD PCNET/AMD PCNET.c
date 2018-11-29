/*
|----------------------------------------------------------|
| 16 бит | 32 бита | режим работы                          |
|----------------------------------------------------------|
| 0                | 16 MAC адрес                          |
|----------------------------------------------------------|
| 0x10   | 0x10    | RDP - регистр данных для CSR          |
|----------------------------------------------------------|
| 0x12   | 0x14    | RAP - индексный регистр для CSR и BCR |
|----------------------------------------------------------|
| 0x14   | 0x18    | регистр сброса                        |
|----------------------------------------------------------|
| 0x16   | 0x1C    | BDP - регистр данных для BCR          |
|----------------------------------------------------------|

Адреса регистров в разных режимах работы устройства(16 бит и 32 бита).
*/


typedef struct
{
    N_32 packet_address;
    N_16 data_length; //непонятно как считается. The BCNT fields of the transmit and receive descriptors are 12-bit negative numbers representing the twos complement of the buffer size in bytes
    N_8  status1;
    N_8  status2;
    N_32 flags;
    N_32 reserved;
}
Receive_Transmit_Descriptor;


typedef struct
{
    N_16                          mode;
    N_8                           receive_buffer_count;  //степень 2-ки, максимум 9 (512 буферов)
    N_8                           transmit_buffer_count; //степень 2-ки, максимум 9 (512 буферов)
    Byte                          MAC_address[6];
    N_16                          reserved;
    Byte                          filter[8];
    Receive_Transmit_Descriptor  *receive_buffer_address;
    Receive_Transmit_Descriptor  *transmit_buffer_address;
}
Packet_Config;


procedure set_register_index(PCI_Device *AMD_PCNET_device, N_32 register_index)
{
    out_32(AMD_PCNET_device->BAR[0] + 0x14, register_index);
}


function N_32 read_from_CSR_register(PCI_Device *AMD_PCNET_device, N_32 CSR_register_index)
{
    set_register_index(AMD_PCNET_device, CSR_register_index);
    return in_32(AMD_PCNET_device->BAR[0] + 0x10);
}


procedure write_in_CSR_register(PCI_Device *AMD_PCNET_device, N_32 CSR_register_index, N_32 data)
{
    set_register_index(AMD_PCNET_device, CSR_register_index);
    out_32(AMD_PCNET_device->BAR[0] + 0x10, data);
}


function N_32 read_from_BCR_register(PCI_Device *AMD_PCNET_device, N_32 CSR_register_index)
{
    set_register_index(AMD_PCNET_device, CSR_register_index);
    return in_32(AMD_PCNET_device->BAR[0] + 0x1c);
}


procedure write_in_BCR_register(PCI_Device *AMD_PCNET_device, N_32 CSR_register_index, N_32 data)
{
    set_register_index(AMD_PCNET_device, CSR_register_index);
    out_32(AMD_PCNET_device->BAR[0] + 0x1c, data);
}


procedure configure_AMD_PCNET(PCI_Device *AMD_PCNET_device)
{
    Byte *MAC_address = AMD_PCNET_device->BAR[1];
    write_hex_array(get_default_text_screen_output(), MAC_address, 6);

    //reset
    N_32 res1 = in_32(AMD_PCNET_device->BAR[0] + 0x18);
    N_16 res2 = in_16(AMD_PCNET_device->BAR[0] + 0x14);

    //sleep 1ms
    cycle(0, 100000000, 1)
    end_cycle

    //set 32 bit mode
    out_32(AMD_PCNET_device->BAR[0] + 0x10, 0);

    //set SWSTYLE
    N_32 CSR_58 = read_from_CSR_register(AMD_PCNET_device, 58);
    write_in_CSR_register(AMD_PCNET_device, 58, CSR_58 & 0xfff0 | 2);

    //set ASEL (auto select 10 / 100baseT)
    N_32 BCR_2 = read_from_BCR_register(AMD_PCNET_device, 2);
    write_in_BCR_register(AMD_PCNET_device, 2, BCR_2 | 0b10);

    Receive_Transmit_Descriptor tdes[9];
    Receive_Transmit_Descriptor rdes[9];

    Byte buffer[1536];
    tdes->packet_address = buffer;

    Packet_Config config;

    config.mode = 0;
    config.receive_buffer_count = 9;
    config.transmit_buffer_count = 9;

    cycle(0, 6, 1)
        config.MAC_address[i] = MAC_address[i];
    end_cycle
    
    cycle(0, 8, 1)
        config.filter[i] = 0;
    end_cycle
    
    config.reserved = 0;
    config.receive_buffer_address = rdes;
    config.transmit_buffer_address = tdes;

    //configure card
    write_in_CSR_register(AMD_PCNET_device, 1, ((N_32)&config) & 0xffff);
    write_in_CSR_register(AMD_PCNET_device, 2, ((N_32)&config) >> 16);

    N_32 CSR_0;

    //initialize
    CSR_0 = read_from_CSR_register(AMD_PCNET_device, 0);
    write_in_CSR_register(AMD_PCNET_device, 0, CSR_0 | 1);

    while(!(read_from_CSR_register(AMD_PCNET_device, 0) & 0b10000000));

    //start
    CSR_0 = read_from_CSR_register(AMD_PCNET_device, 0);
    write_in_CSR_register(AMD_PCNET_device, 0, CSR_0 & 0b11111111111111111111111111111010 | 0b1010);

    buffer[0] = 'H';
    buffer[1] = 'i';

    //send packet
    tdes->status2 |= 0b11;
    tdes->data_length = -1536 & 0x0fff | 0xf000;
    tdes->status2 |= 0x80;
}