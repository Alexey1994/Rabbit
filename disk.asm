load_kernel:
	mov ah, 42h   ; читать сектор в LBA-режиме
	mov dl, 80h
	mov si, packet
	int 13h

	ret

packet:
	packet_size    db 10h        ; размер пакета 10h байт
	reserved       db 00h        ; заначка для будущих расширений
	N_SEC          dw 01h     ; читаем один сектор
	buf_seg        dw 07e00h     ; segment:offset pointer to the memory buffer - куда читать
	buf_off        dw 0          ; смещение буфера-приемника
	X_SEC          dq 0          ; номер первого сектора для чтения (отсчет с 0)

	;X_SEC          dd 0          ; сюда будет занесен номер сектора для чтения
	;               dd 0          ; реально неиспользуемый хвост 64-битного адреса