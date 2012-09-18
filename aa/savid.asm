code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint10	proc	near
	cmp ah,0
	jnz pp
	or al,128
pp:
	db 0eah
l1:	db 0,0
l2:	db 0,0	
nuovoint10		endp
finepr label byte
iniz:
	mov ah,35h
	mov al,10h
	int 21h
	mov word ptr l1,bx
	mov word ptr l2,es
	push cs
	pop ds
	mov dx,offset nuovoint10
	mov ah,25h
	mov al,10h
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
