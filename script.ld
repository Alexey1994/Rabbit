SECTIONS
{
	. = 0x8000;
	.text : { * (.text); }

	. = 0x9000;
	.data : { * (.data); }

    . = 0x10000;
    .bss : { * (.bss); }
}