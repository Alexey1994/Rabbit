#ifndef SYSTEM_IO_H_INCLUDED
#define SYSTEM_IO_H_INCLUDED


function  N_8  in_8   (N_16 port);
procedure      out_8  (N_16 port, N_8 data);

function  N_16 in_16  (N_16 port);
procedure      out_16 (N_16 port, N_16 data);

function  N_32 in_32  (N_16 port);
procedure      out_32 (N_16 port, N_32 data);


#include "IO.c"

#endif //SYSTEM_IO_H_INCLUDED