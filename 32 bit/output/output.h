#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED


#include "../data structures/character/character.h"


typedef struct
{
    Byte       *source;
    procedure (*write_byte)(Byte *source, Byte byte);
    procedure (*deinitialize_source)(Byte *source);
}
Output;


procedure initialize_output   (Output *output, Byte *source, procedure (*write_byte)(Byte *source, Byte byte));
procedure deinitialize_output (Output *output);

procedure write_byte          (Output *output, Byte byte);
procedure write_character     (Output *output, Character character);
procedure write_N_32          (Output *output, N_32 number);

procedure write_byte_array                 (Output *output, Byte *data, N_32 length);
procedure write_null_terminated_byte_array (Output *output, Byte *data);
procedure write_binary_N_32                (Output *output, N_32 number);
procedure write_binary_N_16                (Output *output, N_16 number);
procedure write_binary_N_8                 (Output *output, N_8 number);
procedure write_binary_R_32                (Output *output, R_32 number);

procedure write_hex_array                  (Output *output, Byte *array, N_32 length);
procedure write_hex_N_16                   (Output *output, N_16 number);
procedure write_hex_N_32                   (Output *output, N_32 number);


#include "output.c"

#endif // OUTPUT_H_INCLUDED
