use16
org  0x7C00
start:

call print
call print
call print

jmp $

%include "print.asm"

finish:
    times 0x1FE-finish+start db 0
db 0x55, 0xAA

data db 'Alexey Borisenko'