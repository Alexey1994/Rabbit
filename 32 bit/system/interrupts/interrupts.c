#define NUMBER_OF_INTERRUPTS 256


typedef enum
{
    _80386_32_BIT_TASK_GATE      = 0b0101,
    _80286_16_BIT_INTERRUPT_GATE = 0b0110,
    _80286_16_BIT_TRAP_GATE      = 0b0111,
    _80386_32_BIT_INTERRUPT_GATE = 0b1110,
    _80386_32_BIT_TRAP_GATE      = 0b1111
}
Gate_Types;


typedef struct
{
    N_16        offset_1;           //bits 0..15
    N_16        selector;           //GDT selector
    N_8         unused;             //zero
    Gate_Types  gate_type: 4;
    N_8         storage_segment: 1; //set to 0 for interrupt and trap gates
    N_8         privilege: 2;       //минимальный уровень привилегий для запуска прерывания, меньше - больше привилегий
    N_8         present: 1;         //0 для неиспользуемых
    N_16        offset_2;           //bits 16..31
}
IDT_Table_Item;


typedef struct
{
    N_16             length;
    IDT_Table_Item  *base;
}
IDT_Table_Address;


IDT_Table_Item *idt_table = 0;//[NUMBER_OF_INTERRUPTS];

/*
//void interrupt_handler();
//void _interrupt_handler();
int interrupt_handler;

asm (
    //"mov 1, $0x0B8000\n"
    "pusha\n"
    "popa\n"
    "movb $0x20, %al\n"
    "outb %al, $0x20\n"
    "outb %al, $0xA0\n"
    "popa\n"
    "iret"
);
/*
void _interrupt_handler()
{

}*/


procedure interrupt_handler()
{
    //int k = 0x123456;
    //write_null_terminated_byte_array(get_default_text_screen_output(), "int\n");

    //Byte *t = 0x0B8000;
    //*t = 'A';

    asm (
        "mov %0, 0x0B8000\n"
        //"leave\n"
        "iret"
        :
        :"a"(1)
    );
}


procedure initialize_interrupts()
{
    IDT_Table_Address *address = 0xa00000;

    N_32 interrupt_address = &interrupt_handler;

    asm (
        //"pushf\n"
        "cli"
        :
        :
    );

    cycle(0, NUMBER_OF_INTERRUPTS, 1)
        idt_table[i].offset_1        = 0;//interrupt_address;
        idt_table[i].offset_2        = 0;//interrupt_address >> 16;
        idt_table[i].selector        = 0;//8;
        idt_table[i].unused          = 0;
        idt_table[i].gate_type       = 0;//_80386_32_BIT_INTERRUPT_GATE;
        idt_table[i].storage_segment = 0;//0;
        idt_table[i].privilege       = 0;//0;
        idt_table[i].present         = 0;//1;
    end_cycle

    idt_table[32].offset_1        = interrupt_address;
    idt_table[32].offset_2        = interrupt_address >> 16;
    idt_table[32].selector        = 8;
    idt_table[32].unused          = 0;
    idt_table[32].gate_type       = _80386_32_BIT_INTERRUPT_GATE;
    idt_table[32].storage_segment = 0;
    idt_table[32].privilege       = 0;
    idt_table[32].present         = 1;

    //address.length = sizeof(IDT_Table_Item) * NUMBER_OF_INTERRUPTS;
    //address.base   = idt_table;
    *((N_16*)address) = sizeof(IDT_Table_Item) * NUMBER_OF_INTERRUPTS;
    *((N_32*)(((N_16*)address) + 1)) = idt_table;
int k = 0x123456;
    asm (
        "lidt 0xa00000\n"
        //"popf\n"
        "sti\n"
        //"int %1"
        :
        : "a"(&address), "Nd"(0x81)
    );
}