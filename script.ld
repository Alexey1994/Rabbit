SECTIONS
{
	. = 0;
	.text : { * (.text); }

	. = 2000;
	.data : { * (.data); }
}