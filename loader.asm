use16
org  0x7C00
start:

;call print_string
;call print_string
;call print_string

;mov ax, 0
;call print_byte

;ret

call load_kernel

mov al, [0x7e00]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e01]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e02]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e03]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e04]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e05]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e06]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e07]
call print_byte

mov al, ' '
call print_character
mov al, [0x7e08]
call print_byte

mov al, ' '
call print_character
mov al, 208
call print_byte

jmp $

ret

%include "print.asm"
%include "disk.asm"

finish:
    times 0x1FE-finish+start db 0
db 0x55, 0xAA

data db 'Alexey Borisenko'