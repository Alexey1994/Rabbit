#ifndef SYSTEM_MEMORY_H_INCLUDED
#define SYSTEM_MEMORY_H_INCLUDED


function  Byte* allocate_memory (N_32 size);
procedure       free_memory     (Byte *allocated_memory);


#include "memory.c"

#endif //SYSTEM_MEMORY_H_INCLUDED