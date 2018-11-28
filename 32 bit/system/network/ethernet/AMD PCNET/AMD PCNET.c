//CSR - регистр управления состоянием
//BCR - регистр управления шиной
//RAP - индексный регистр для CSR и BCR
//RDP - регистр данных для CSR
//BDP - регистр данных для BCR


typedef struct
{
    N_16  mode;
    N_8   receive_buffer_count;  //умножается на 8, максимум 512
    N_8   transmit_buffer_count; //умножается на 8, максимум 512
    Byte  MAC_address[6];
    N_16  reserved;
    Byte  filter[8];
    N_32  receive_buffer_address;
    N_32  transmit_buffer_address;
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


void configure_AMD_PCNET(PCI_Device *AMD_PCNET_device)
{
    Byte *MAC_address = AMD_PCNET_device->BAR[1];

    write_hex_array(get_default_text_screen_output(), MAC_address, 6);

    //reset
    N_16 res1 = in_16(AMD_PCNET_device->BAR[0] + 0x18);
    N_32 res2 = in_32(AMD_PCNET_device->BAR[0] + 0x14);

    write_byte(get_default_text_screen_output(), '\n');

    cycle(0, 100000000, 1)
    end_cycle

    //set 32 bit mode
    out_32(AMD_PCNET_device->BAR[0] + 0x10, 0);

    //set SWSTYLE
    N_32 CSR_58 = read_from_CSR_register(AMD_PCNET_device, 58);
    CSR_58 &= 0xfff0;
    CSR_58 |= 2;
    write_in_CSR_register(AMD_PCNET_device, 58, CSR_58);

    Packet_Config config;

    config.mode = 0;
    config.receive_buffer_count = 3;
    config.transmit_buffer_count = 3;

    cycle(0, 6, 1)
        config.MAC_address[i] = MAC_address[i];
    end_cycle
    
    cycle(0, 8, 1)
        config.filter[i] = 0;
    end_cycle
    
    config.reserved = 0;
    config.receive_buffer_address = 1234567;
    config.transmit_buffer_address = 2345678;

    write_in_CSR_register(AMD_PCNET_device, 1, ((N_32)&config) & 0xffff);
    write_in_CSR_register(AMD_PCNET_device, 2, (((N_32)&config) >> 16) & 0xffff);

    
    //write_hex_N_32(get_default_text_screen_output(), in_32(AMD_PCNET_device->BAR[1] + 0x14));

    //N_32 BCR_18 = read_from_BCR_register(AMD_PCNET_device, 18);
    //write_hex_N_32(get_default_text_screen_output(), (BCR_18 >> 7) & 1);

    N_32 CSR_0;

    //initialize
    CSR_0 = read_from_CSR_register(AMD_PCNET_device, 0);
    CSR_0 |= 0b1;
    write_in_CSR_register(AMD_PCNET_device, 0, CSR_0);

    while(!(read_from_CSR_register(AMD_PCNET_device, 0) & 0b10000000));
    write_null_terminated_byte_array(get_default_text_screen_output(), "initialized\n");

    //start
    CSR_0 = read_from_CSR_register(AMD_PCNET_device, 0);
    CSR_0 &= 0b11111111111111111111111111111010;
    CSR_0 |= 0b10;
    write_in_CSR_register(AMD_PCNET_device, 0, CSR_0);
    //write_reset(BARs[1]);

    CSR_0 = read_from_CSR_register(AMD_PCNET_device, 0);
    CSR_0 |= 0b1000;
    write_in_CSR_register(AMD_PCNET_device, 0, CSR_0);

    Byte *tx = 2345678;

    tx[0] = 90;
}