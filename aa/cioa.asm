code		segment
	assume cs:code,ds:code
	org 100h
start:
	jmp iniz
msg:	db 'Ciao',0
iniz:
	mov ax,10
	mov al,65
	mov ah,7h
	mov bx,0b800h
	push bx
	pop es
	xor bx,bx
	mov[es:bx],ax
	int 20h
code		ends
	end start
