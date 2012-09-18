code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint13	proc	near
	push ax
	push bx
	push cx
	push dx
	mov ah,9
	mov al,7
	mov bh,0
	mov bl,14
	mov cx,1
	int 10h
	pop dx
	pop cx
	pop bx
	pop ax
	db 0eah
l1:	db 0,0
l2:	db 0,0	
nuovoint13		endp
finepr label byte
iniz:
	mov ah,35h
	mov al,13h
	int 21h
	mov word ptr l1,bx
	mov word ptr l2,es
	push cs
	pop ds
	mov dx,offset nuovoint13
	mov ah,25h
	mov al,13h
	int 21h
	push cs
	pop es
	mov es,es:[2ch]
	mov ah,49h
	int 21h
	lea dx,finepr
	int 27h
code		ends
	end start
