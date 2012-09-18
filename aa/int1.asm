code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
i1s:	dw 0
i1o:    dw 0
newi1:
	push ax
	push bx
	push cx
	push dx
	
	mov ah,2
	mov dl,90h
	int 21h


	pop dx
	pop cx
	pop bx
	pop ax
	iret
iniz:
	mov ah,35h
	mov al,1
	int 21h
	mov word ptr i1o,bx
	mov ax,es
	mov word ptr i1s,ax
	mov ah,25h
	mov al,1
	lea dx,newi1
	push cs
	pop ds
	int 21h
	pushf
	pop ax
	or ax,256
	push ax
	popf

	mov bl,6
	inc bx
	xor bx,bx

	pushf
	pop ax
	xor ax,256
	push ax
	popf
	mov dx,word ptr i1o
	mov ax,word ptr i1s
	push ax
	pop ds
	mov ah,25h
	mov al,1
	int 21h
	push cs
	pop ds
	int 20h
code 		ends
	end start
