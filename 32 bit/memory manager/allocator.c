#include "allocator.h"
#include "../display output.h"


static Byte *memory = (Byte*)0x400000;


void print_memory()
{
	Size *i;

	for(i = (Size*)(memory - sizeof(Size) - 1); (Size)i >= 0x400000; i = (Size*)( (Byte*)i - *i - sizeof(Size) - 1 ) )
	{
		print_integer(*i);
		print_integer( ((Byte*)i)[sizeof(Size)] );
		print_character(':');
	}
}


Byte* create_memory(Size size)
{
	Byte *allocated_memory;

	allocated_memory = memory;
	memory += size;

	*(Size*)memory = size;
	memory += sizeof(Size);

	*memory = 1;
	++memory;

	return allocated_memory;
}


static void defragmentation()
{
	Size *i;
	Byte  is_busy;

	for(i = (Size*)(memory - sizeof(Size) - 1); (Size)i >= 0x400000; i = (Size*)( (Byte*)i - *i - sizeof(Size) - 1 ) )
	{
		is_busy = ((Byte*)i)[sizeof(Size)];

		if(is_busy)
			return;

		memory = (Byte*)i - *i;
	}
}


void destroy_memory(Byte *allocated_memory)
{
	Size *i;
	Byte *current_block;

	for(i = (Size*)(memory - sizeof(Size) - 1); (Size)i >= 0x400000; i = (Size*)( (Byte*)i - *i - sizeof(Size) - 1 ) )
	{
		current_block = (Byte*)i - *i;

		if(current_block == allocated_memory) //block finded
		{

			((Byte*)i)[sizeof(Size)] = 0;
			defragmentation();
			return;
		}
	}

	//block not finded
}