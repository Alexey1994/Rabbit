#include "ports.h"


Byte in(short port)
{
	Byte data;

	asm volatile(
		"inb %1, %0"
		: "=a"(data)
		: "Nd"(port)
	);

	return data;
}


void out(short port, Byte data)
{
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}