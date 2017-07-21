void kernel();

void start()
{
	kernel();
}
/*
#include "display output.h"

#include "drivers/ports.h"
#include "drivers/sound blaster 16/output stream.h"

#include "memory manager/allocator.h"
*/


#include "types.h"
#include "extends.h"
#include "output stream/output stream.h"


void print_character(char *screen_, char character)
{
	static char         *screen  = 0x0B8000;
	//static unsigned int  x_coord = 0;
	//static unsigned int  y_coord = 0;

	*screen = character;
	screen += 2;
}


void print_char_array(char *char_array)
{

}


void kernel()
{
	Output_Stream screen;

	initialize_output_stream(&screen, 0x0B8000, print_character);
	write_decimal_integer_number_in_output_stream(&screen, 123456);

	/*char *t = "b";
	static char *screen = 0x0B8000;

	screen[0] = *t;*/

	//print_character('H');
	//print_character('i');



	/*print_character('H');
	print("Hi");
	print(0x500);

	for(;;);

	Byte* memory1 = create_memory(10);
	Byte* memory2 = create_memory(10);

	destroy_memory(memory1);
	destroy_memory(memory2);

	create_memory(123);

	print_memory();*/
}