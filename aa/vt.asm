vt_font8x8	proc	near
;-----------------------------------------------------------------------;
; Questa Funzione porta a 43 righe lo shermo				;
; Nessun parametro di entrata						;
;-----------------------------------------------------------------------;
	push ax
	mov ah,11h
	mov al,12h
	int 10h
	pop ax
	ret
vt_font8x8		endp
vt_cls proc near
;-----------------------------------------------------------------------;
;	Questa Funzione Cancella lo schermo a 43-25 righe.		;
;									;
;	Parametri:							;
;									;
;	BH :il codice del colore(attribbuto) per le righe vuote		;
;-----------------------------------------------------------------------;
	push ax
	push bx
	push cx
	push dx
	mov ah,6
	xor al,al
	mov bh,14
	xor cx,cx
	mov dh,43
	mov dl,80
	int 10h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
vt_cls		endp
vt_gotoxy	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura imposta la posizione del cursore.		;
;									;
;	DH : Nuero riga							;
;	DL : Nuero colonna						;
;-----------------------------------------------------------------------;
	push ax
	push bx
	mov ah,2
	mov bh,0
	int 10h
	pop bx
	pop ax
	ret
vt_gotoxy		endp
vt_read_cur_pos	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura legge la posizione attuale del cursore.	;
;									;
;     entrata:								;
;	BH : Nuero pagina						;
;     Uscita:								;
;	BH : Nuero pagina						;
;	CH : Prima linea di scansione in cui si trova il cursore	;
;	CL : Ultima riga						;
;	DH : Nuero riga							;
;	DL : Nuero Colonna						;
;-----------------------------------------------------------------------;
	push ax
	push cx
	mov ah,3
	int 10h
	pop cx
	pop ax
	ret
vt_read_cur_pos		endp
vt_write_dos_str	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura scrive una stringa alla posizione del 		;
;	cursore utilizzando la funzione DOS.				;
;									;
;	DS:DX : puntatore alla stringa					;
;-----------------------------------------------------------------------;
	push ax
	mov ah,9
	int 21h
	pop ax
	ret
vt_write_dos_str		endp
vt_fontn	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura porta a 25 le linee dello schermo.		;
;-----------------------------------------------------------------------;
	push ax
	mov ah,11h
	mov al,11h
	int 10h
	pop ax
	ret
vt_fontn		endp
vt_write_char	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Funzione scrive un carattere sullo schermo alla posizione;
;	corrente del cursore utilizando la funzione BIOS.		;
;									;
;	DL : byte o carattere da stampare.				;
;	byte ptr attr_char: attributo.					;
;-----------------------------------------------------------------------;
	push ax
	push bx
	push cx
	push dx
	mov ah,9
	mov bh,0
	mov cx,1
	mov al,dl
	call vt_getcolor
	int 10h
	call vt_cur_right
	pop dx
	pop cx
	pop bx
	pop ax
	ret
vt_write_char		endp
vt_setcolor	proc	near
;-----------------------------------------------------------------------;
;	Questa Procedura permette di definire l'attributo del		;
;	carattere da stampare.						;
;									;
;	BL : colore del carattere.					;
;-----------------------------------------------------------------------;
	mov byte ptr attr_char,bl
	ret
vt_setcolor		endp
vt_getcolor	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Procedura permette di sapere il colore che si sta'	;
;	usando per scrivere.						;
;									;
;      ritorna:								;
;	BL : Numero colore.						;
;-----------------------------------------------------------------------;
	mov bl,byte ptr attr_char
	ret
vt_getcolor		endp
vt_cur_right	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Procedura sposta il cursore di una posizione		;
;	verso destra.							;
;-----------------------------------------------------------------------;
	push ax
	push bx
	push cx
	push dx
	mov bh,0
	call vt_read_cur_pos
	inc dl
	cmp dl,79
	jbe move_cursor
	call vt_send_crlf
	jmp done_cursor_right
move_cursor:
	call vt_gotoxy
done_cursor_right:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
vt_cur_right		endp
vt_send_crlf	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Procedura ritorna a capo e avanza riga.			;
;-----------------------------------------------------------------------;
	push ax
	push dx
	mov ah,2
	mov dl,13
	int 21h
	mov dl,10
	int 21h
	pop dx
	pop ax
	ret
vt_send_crlf		endp
vt_write_char_n_times	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Procedura serve per scrivere un carattere un		;
;	certo numero di volte.						;
;									;
;	DL : Carattere da stampare					;
;	CX : Numero di copie del carattere				;
;-----------------------------------------------------------------------;
	push cx
n_times:
	call vt_write_char
	loop n_times
	pop cx
	ret
vt_write_char_n_times endp
vt_write_str	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa Procedura Serve a stampare una stringa con colore	;
;	La stringa deve terminare cin DB 0.				;
;									;
;	DS:DX : Indirizzo della stringa					;
;-----------------------------------------------------------------------;
	push ax
	push dx
	push si
	pushf
	cld
	mov si,dx
string_loop:
	lodsb
	or ax,ax
	jz end_of_string
	mov dl,al
	call vt_write_char
	jmp string_loop
end_of_string:
	popf
	pop si
	pop dx
	pop ax
	ret
vt_write_str		endp
vt_write_hex_digit	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura converte i 4 bit inferiori di DL in cifra	;
;	esadecimale e la scrive sullo schermo.				;
;									;
;	DL : 4 bit inferiori che contengono il numero esadeciale	;
;		(mov DL,0Fh stampa 'F').				;
;-----------------------------------------------------------------------;
	push dx
	cmp dl,10
	jae hex_letter
	add dl,'0'
	jmp write_digit
hex_letter:
	add dl,'A'-10
write_digit:
	call vt_write_char
	pop dx
	ret
vt_write_hex_digit		endp
vt_write_hex	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura serve a stampare 1 byte in esadecimale		;
;									;
;	DL : byte da stampare(mov DL,FEh)				;
;-----------------------------------------------------------------------;
	push cx
	push dx
	mov dh,dl
	mov cx,4
	shr dl,cl
	call vt_write_hex_digit
	mov dl,dh
	and dl,0fh
	call vt_write_hex_digit
	pop dx
	pop cx
	ret
vt_write_hex		endp
vt_write_decimal	proc	near
;-----------------------------------------------------------------------;
;									;
;	Questa procedura serve a stampare sullo schermo il contenuto	;
;	decimale di DX.							;
;									;
;	DX : nuero senza segno a 16-bit.				;
;-----------------------------------------------------------------------;
	push ax
	push cx
	push dx
	push si
	mov ax,dx
	mov si,10
	xor cx,cx
non_zero:
	xor dx,dx
	div si
	push dx
	inc cx
	or ax,ax
	jne non_zero
write_digit_loop:
	pop dx
	call vt_write_hex_digit
	loop write_digit_loop
end_decimal:
	pop si
	pop dx
	pop cx
	pop ax
	ret
vt_write_decimal		endp
attr_char:	db 14
