#include "stream.h"


static int pow_10(unsigned int n)
{
	int pow = 1;

	while(n)
	{
		pow *= 10;
		--n;
	}

	return pow;
}


void put_integer(int num, void(*put_byte)(Byte byte))
{
	int t      = num;
	int length = 0;

	while(t)
	{
		++length;
		t = t/10;
	}

	if(num < 0)
	{
		put_byte('-');
		num *= -1;
	}

	if(!num)
		print_character('0');

	while(length)
	{
		print_character(num / pow_10(length - 1) % 10 + '0');
		--length;
	}
}