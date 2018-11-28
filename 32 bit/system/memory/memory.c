static Byte *memory = (Byte*)0x400000;

/*
void print_memory()
{
    Size *i;

    for(i = (Size*)(memory - sizeof(Size) - 1); (Size)i >= 0x400000; i = (Size*)( (Byte*)i - *i - sizeof(Size) - 1 ) )
    {
        print_integer(*i);
        print_integer( ((Byte*)i)[sizeof(Size)] );
        print_character(':');
    }
}*/


function Byte* allocate_memory (N_32 size)
{
    Byte *allocated_memory;

    allocated_memory = memory;
    memory += size;

    *(N_32*)memory = size;
    memory += sizeof(N_32);

    *memory = 1;
    ++memory;

    return allocated_memory;
}


private procedure defragmentation ()
{
    N_32    *i;
    Boolean  is_busy;

    for(i = (N_32*)(memory - sizeof(N_32) - 1); (N_32)i >= 0x400000; i = (N_32*)( (Byte*)i - *i - sizeof(N_32) - 1 ) )
    {
        is_busy = ((Byte*)i)[sizeof(N_32)];

        if(is_busy)
            return;

        memory = (Byte*)i - *i;
    }
}


procedure free_memory (Byte *allocated_memory)
{
    N_32 *i;
    Byte *current_block;

    for(i = (N_32*)(memory - sizeof(N_32) - 1); (N_32)i >= 0x400000; i = (N_32*)( (Byte*)i - *i - sizeof(N_32) - 1 ) )
    {
        current_block = (Byte*)i - *i;

        if(current_block == allocated_memory) //block finded
        {

            ((Byte*)i)[sizeof(N_32)] = 0;
            defragmentation();
            return;
        }
    }

    //block not finded
}