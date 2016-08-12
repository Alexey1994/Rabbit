print:
	mov ah, 0x0e
	mov cx, 1
	mov ebx, message

	next_character:
		mov al, [bx]

		cmp al, 0
		je end_print

		int 10h
		inc bx
	jmp next_character

end_print:
	ret

message db 'Hello',0