SECTIONS
{
	. = 0x10000;
	.text : { * (.text); }

	. = 0x12000;
	.data : { * (.data); }

    . = 0x13000;
    .bss : { * (.bss); }
}