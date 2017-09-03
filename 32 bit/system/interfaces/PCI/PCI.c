unsigned int read_from_PCI (Byte bus, Byte device, Byte function, Byte register_number)
{
	unsigned int device_address =
		  0b10000000000000000000000000000000 //enable bit
		| (bus << 16)
		| (device << 11)
		| (function << 8)
		| ((register_number << 2) & 0b11111100);

	out32(0xcf8, device_address);
	return in32(0xcfc);
}


void write_in_PCI_device(PCI_Device *device, Byte register_number, unsigned int data)
{
	unsigned int device_address =
		  0b10000000000000000000000000000000 //enable bit
		| (device->ID.bus << 16)
		| (device->ID.device << 11)
		| (device->ID.function << 8)
		| ((register_number << 2) & 0b11111100);

	out32(0xcfc, data);
}


void print_PCI_device(PCI_Device *device)
{
	print_null_terminated_byte_array("bus:");
	print_unsigned_integer(device->ID.bus);

	print_null_terminated_byte_array(" device:");
	print_unsigned_integer(device->ID.device);

	print_null_terminated_byte_array(" PCI vendor:");
	print_unsigned_integer(device->vendor);

	print_null_terminated_byte_array(" PCI device:");
	print_unsigned_integer(device->device);

	print_null_terminated_byte_array(" revision ID:");
	print_unsigned_integer(device->revision);

	print_null_terminated_byte_array(" class:");
	print_unsigned_integer(device->class);

	print_null_terminated_byte_array(" subclass:");
	print_unsigned_integer(device->subclass);
}