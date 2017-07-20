load_kernel:
	mov ah, 42h   ; читать сектор в LBA-режиме
	mov dl, 80h
	mov si, packet
	int 13h

	ret

packet:
	packet_size    db 10h        ; размер структуры
	reserved       db 0          ; зарезервировано
	N_SEC          dw 20         ; читаем 20 * 512 байт
	buffer         dd 0          ;
	X_SEC          dq 1          ; номер первого сектора для чтения (отсчет с 0)
	dummy          dq 0