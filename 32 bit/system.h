#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED


typedef unsigned char          Bit;
typedef unsigned char          Byte;
typedef unsigned char          Boolean;

typedef char                   Z_8;
typedef short int              Z_16;
typedef long int               Z_32;
typedef long long int          Z_64;

typedef unsigned char          N_8;
typedef unsigned short int     N_16;
typedef unsigned long int      N_32;
typedef unsigned long long int N_64;

typedef float                  R_32;
typedef double                 R_64;


#define private    static
#define procedure  void
#define function

#define end }

#define loop\
    for(;;)\
        {

#define cycle(from, to, step)\
{\
    N_32 i;\
    for(i = (from); i < (to); i += (step))\
        {

#define end_cycle }}

#endif // SYSTEM_H_INCLUDED
