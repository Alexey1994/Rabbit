SECTIONS
{
	. = 0x8000;
	.text : { * (.text); }

	. = 500;
	.data : { * (.data); }
}