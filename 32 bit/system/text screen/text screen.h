#ifndef TEXT_SCREEN_H_INCLUDED
#define TEXT_SCREEN_H_INCLUDED


#include "../../output/output.h"


typedef struct
{
	Byte         *address;
	unsigned int  x_coord;
	unsigned int  y_coord;
	unsigned int  x_max;
	unsigned int  y_max;
}
Text_Screen;


void         initialize_text_screen(Text_Screen *text_screen, Byte *address, unsigned int x_max, unsigned int y_max);
Text_Screen* get_default_text_screen();
Output*      get_default_text_screen_output();

void         write_byte_in_text_screen(Text_Screen *screen, Byte byte);

void         print_byte(Byte byte);
void         print_null_terminated_byte_array(Byte *byte_array);
void         print_unsigned_integer(unsigned int number);


#include "text screen.c"

#endif //TEXT_SCREEN_H_INCLUDED