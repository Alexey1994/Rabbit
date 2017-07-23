load_kernel:
	mov ah, 0x42   ; читать сектор в LBA-режиме
	mov dl, 0x80
	mov si, packet
	int 0x13
	jc error

	ret

error:
	mov ah, 0x0e
	mov cx, 1
	mov al, 1
	int 10h
	jmp $

packet:
	packet_size    db 10h        ; размер структуры
	reserved       db 0          ; зарезервировано
	N_SEC          dw 10         ; читаем 10 * 512 байт
	buffer_address dw 0x8000
	buffer_offset  dw 0x0000
	X_SEC          dd 1          ; номер первого сектора для чтения (отсчет с 0)
	dummy          dd 0