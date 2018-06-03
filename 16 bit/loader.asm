org 0x7C00

start:
	mov ax, $
	mov ax, cs
	mov ds, ax
	mov ss, ax

	mov ax, 100
	mov sp, 0x8000 - 1     ; stack size for loader = 0x8000 - 0x7c00 - 512 = 512 byte
	sti

	mov ah, 0x4f           ; VESA functions
	mov al, 0x02           ; set video mode
	mov bx, 0x4112         ; 640x480 32bit
	int 10h

	mov ax,  0x4f01
	mov cx,  0x4118
	mov edi, 0x7E00        ; video info
	int 10h

	call load_kernel

	lgdt [GDT_pointer]
	
	cli
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 8:code_32         ; CS register = 8, IP register = code_32

%include "16 bit\load kernel.asm"

use32
code_32:
	mov eax, 16
	mov ds, ax
	mov ss, eax

	mov eax, 12345678
	mov esp, eax

	call 0x8000
	jmp $

align 16

GDT:
    dq 0                  ; dummy

                          ; CODE (CS register = 8)
    dw 0xffff             ; Segment Limit
    dw 0                  ; Base address
    db 0                  ; Base address
    db 0b10011010         ; segment present   = 1 (segment is valid)
                          ; ring              = 00 (maximum)
                          ; descriptor type   = 1 (code and data)
                          ; type              = 1010 (read/execute)
    db 0b11001111         ; Granularity       = 1 (max memory size = 4096 * Segment Limit)
                          ; 32 bit addressing = 1 (enabled)
                          ; L                 = 0
                          ; AVL               = 0
                          ; Segment Limit     = 1111
    db 0                  ; Base address

                          ; DATA (DS register = 16)
    dw 0xffff             ; Segment Limit
    dw 0                  ; Base address
    db 0                  ; Base address
    db 0b10010010         ; segment present   = 1 (segment is valid)
                          ; ring              = 00 (maximum)
                          ; descriptor type   = 1 (code and data)
                          ; type              = 0010 (read/write)
    db 0b11001111         ; Granularity       = 1 (max memory size = 4096 * Segment Limit)
                          ; 32 bit addressing = 1 (enabled)
                          ; L                 = 0
                          ; AVL               = 0
                          ; Segment Limit     = 1111
    db 0                  ; Base address

GDT_pointer:
	dw $ - GDT - 1
	dd GDT

times 510 - ($ - start) db 0
db 0x55, 0xAA