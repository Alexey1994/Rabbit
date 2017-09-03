unsigned int read_from_PCI_device (PCI_Device *device, Byte register_number)
{
	unsigned int device_address =
		  0b10000000000000000000000000000000 //enable bit
		| (device->ID.bus << 16)
		| (device->ID.device << 11)
		| (device->ID.function << 8)
		| ((register_number << 2) & 0b11111100);

	out_32(0xcf8, device_address);
	return in_32(0xcfc);
}


void write_in_PCI_device(PCI_Device *device, Byte register_number, unsigned int data)
{
	unsigned int device_address =
		  0b10000000000000000000000000000000 //enable bit
		| (device->ID.bus << 16)
		| (device->ID.device << 11)
		| (device->ID.function << 8)
		| ((register_number << 2) & 0b11111100);

	out_32(0xcfc, data);
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


void find_PCI_devices (void(*on_finded)(PCI_Device *device))
{
	PCI_Device device;

	unsigned int current_bus;
	unsigned int current_device;

	device.ID.function = 0;

	for(current_bus = 0; current_bus < 256; ++current_bus)
	{
		for(current_device = 0; current_device < 32; ++current_device)
		{
			unsigned int config = read_from_PCI_device(&device, 0);//read_from_PCI(current_bus, current_device, 0, 0);

			if(config != 0xffffffff)
			{
				device.ID.bus    = current_bus;
				device.ID.device = current_device;

				device.vendor = config & 0xffff;
				device.device = config >> 16;

				config = read_from_PCI_device(&device, 2);//read_from_PCI(device.ID.bus, device.ID.device, 0, 2);
				device.class = config >> 24;
				device.subclass = (config >> 16) & 0xff;
				device.revision = config & 0xff;

				on_finded(&device);

				//print_PCI_device(&device);
				//print_null_terminated_byte_array("\n");
			}
		}
	}
}