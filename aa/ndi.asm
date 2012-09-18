code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
drive:	db 0
msg:	db'Iaza Disk Information v 1.00á 1991(c) by Iaza Soft.',10,13,'$'
errm:	db'Drive not valid !!!$'
okm:	db'Ok,',10,13,'$'


iniz:
	mov dx,offset msg
	mov ah,9
	int 21h
	mov ah,32h
	mov dl,0
	int 21h
	push ds
	pop es
	push cs
	pop ds
	cmp al,0ffh
	jne ok
	mov dx,offset errm
	mov ah,9
	int 21h
	mov ah,4ch
	int 21h
ok:
	lea dx,okm
	mov ah,9
	int 21h
	mov dl,es:[bx]
	call vt_write_hex
	call vt_send_crlf
	inc bx
	mov dl,es:[bx]
	call vt_write_hex
	call vt_send_crlf
	mov bx,16h
	mov dl,es:[bx]
	call vt_write_hex
	mov ah,4ch
	int 21h
	include vt.asm
code		ends
	end start
