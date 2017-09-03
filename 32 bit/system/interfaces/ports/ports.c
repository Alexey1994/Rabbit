Byte in_8(short port)
{
	Byte data;

	asm volatile(
		"inb %1, %0"
		: "=a"(data)
		: "Nd"(port)
	);

	return data;
}


void out_8(short port, Byte data)
{
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}


unsigned short in_16(short port)
{
	unsigned short data;

	asm volatile(
		"inl %1, %0"
		: "=a"(data)
		: "Nd"(port)
	);

	return data;
}


void out_16(short port, unsigned short data)
{
	asm volatile("outl %0, %1" : : "a"(data), "Nd"(port));
}


void out_32(short port, int data)
{
	asm volatile("outl %0, %1" : : "a"(data), "Nd"(port));
}

int in_32(short port)
{
	int data;

	asm volatile(
		"inl %1, %0"
		: "=a"(data)
		: "Nd"(port)
	);

	return data;
}