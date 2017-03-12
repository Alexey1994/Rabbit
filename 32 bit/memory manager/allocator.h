#ifndef MEMORY_ALLOCATOR_H_INCLUDED
#define MEMORY_ALLOCATOR_H_INCLUDED


#include "../types.h"


void print_memory();
Byte* create_memory(Size size);
void destroy_memory(Byte *allocated_memory);


#endif //MEMORY_ALLOCATOR_H_INCLUDED