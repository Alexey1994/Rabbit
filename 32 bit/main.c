void kernel();

void start()
{
	kernel();
}

#include "display output.h"

#include "drivers/ports.h"
#include "drivers/sound blaster 16/output stream.h"

#include "memory manager/allocator.h"


void kernel()
{
	print_character('H');
	print("Hi");
	print(0x500);

	for(;;);

	Byte* memory1 = create_memory(10);
	Byte* memory2 = create_memory(10);

	destroy_memory(memory1);
	destroy_memory(memory2);

	create_memory(123);

	print_memory();
}