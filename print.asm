print_string:
	mov ah, 0x0e
	mov cx, 1
	mov bx, message

	next_character_print_string:
		mov al, [bx]

		cmp al, 0
		je end_print_string

		int 10h
		inc bx
	jmp next_character_print_string

end_print_string:
	ret


print_character:
	mov ah, 0x0e
	mov cx, 1
	int 10h
	ret


print_byte:
	mov cl, 0                   ;в начале ноль

	mov bl, al
	mov bh, 0
	mov ah, 0

	mov dl, 100
	div dl
	
	cmp al, 0
	je next_symbol_print_byte

	mov cl, 1                   ;в начале не ноль

	add al, '0'
	call print_character

	next_symbol_print_byte:
		mov ax, bx
		mov dl, 10
		div dl

		mov ah, 0
		mov dl, 10
		div dl

		cmp cl, 1
		je print_null_character

		cmp ah, 0
		je last_symbol_print_byte

		print_null_character:
			add ah, '0'
			mov al, ah	
			call print_character

	last_symbol_print_byte:
		mov ax, bx
		mov dl, 10
		div dl

		add ah, '0'
		mov al, ah
		call print_character
	ret


print_integer:
	ret


message db 'Hello',0