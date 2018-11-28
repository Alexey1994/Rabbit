function Boolean is_number(Character c)
{
    if(c>='0' && c<='9')
        return 1;

    return 0;
}


function Boolean is_hex_number(Character c)
{
    if((c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F'))
        return 1;

    return 0;
}


function Boolean is_letter(Character c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_')
        return 1;

    return 0;
}


function Boolean is_space(Character c)
{
    if(c==' ' || c=='\n' || c=='\r' || c=='\t')
        return 1;

    return 0;
}
