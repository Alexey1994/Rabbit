SECTIONS
{
	. = 0;
	.text : { * (.text); }

	. = 1000;
	.data : { * (.data); }
}