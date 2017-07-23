#include "../ports.h"


Byte get_key_code()
{
	return in(0x60);
}