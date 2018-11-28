function N_8 in_8(N_16 port)
{
    N_8 data;

    asm volatile(
        "inb %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );

    return data;
}


procedure out_8(N_16 port, N_8 data)
{
    asm volatile(
        "outb %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}


function N_16 in_16(N_16 port)
{
    N_16 data;

    asm volatile(
        "inw %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );

    return data;
}


procedure out_16(N_16 port, N_16 data)
{
    asm volatile(
        "outw %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}


function N_32 in_32(N_16 port)
{
    N_32 data;

    asm volatile(
        "inl %1, %0"
        : "=a"(data)
        : "Nd"(port)
    );

    return data;
}


procedure out_32(N_16 port, N_32 data)
{
    asm volatile(
        "outl %0, %1"
        :
        : "a"(data), "Nd"(port)
    );
}
