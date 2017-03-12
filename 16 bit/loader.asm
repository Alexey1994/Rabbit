org 0x7C00

start:
	jmp 0:t
 t:
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, $$
	sti

call load_kernel

	lgdt [GDT_pointer]
	
	cli
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 8:code_32

%include "16 bit\disk.asm"

GDT:
	dq 0
	dq 0x00CF9A000000FFFF
	dq 0x00CF92000000FFFF

GDT_pointer:
	dw $ - GDT - 1
	dd GDT

use32
code_32:
	mov eax, 16
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	movzx esp, sp

	;call main
	call 0
	jmp $ 

main:

times 510 - ($ - start) db 0
db 0x55, 0xAA