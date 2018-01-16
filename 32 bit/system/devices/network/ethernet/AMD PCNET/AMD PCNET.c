void write_in_AMD_PCNET(unsigned int base_address, unsigned int data)
{
	out_32(base_address + 0x14, data);
}


void reset_WIO()
{
	
}


void write_in_CSR(unsigned int base_address, unsigned int CSR, unsigned int data)
{
	write_in_AMD_PCNET(base_address, CSR);
	out_32(base_address + 0x10, data);
}


unsigned int read_from_AMD_PCNET(unsigned int base_address, unsigned int CSR_number)
{
	write_in_AMD_PCNET(base_address, CSR_number);
	return in_32(base_address + 0x10);
}


void configure_AMD_PCNET(PCI_Device *device)
{
	unsigned int device_config;
	unsigned int base_address0;

	//device_config = read_from_PCI_device(device, 0);

	//device_config = (device_config & 0xffff0000)
	//	| 0x05;//0b00000101;

	//write_in_PCI_device(device, 4, device_config);
/*
	write_in_PCI_device(device, 4, 0x00000004);
	write_in_PCI_device(device, 4, 0x00035f00);
*/
	//base_address = read_from_PCI_device(device, 4);

	base_address0 = read_from_PCI_device(device, 0x18 + 8);

	print_null_terminated_byte_array("base address ");
	print_unsigned_integer( ((int*)base_address0)[0] );

	//print_unsigned_integer(in32(base_address));

/*
	//to 32 bit mode
	unsigned int csr58 = read_from_AMD_PCNET(base_address, 58);
	csr58 &= 0xfff0;
	csr58 |= 2;
	write_in_CSR(base_address, 58, csr58);*/

	//read_from_AMD_PCNET(base_address, );
/*
	for(;;)
	write_in_AMD_PCNET(base_address, 1234);*/
}