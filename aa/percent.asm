code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
vv:	dw 0
str1:	db'같같같같같같같같같같$'
iniz:
	call vt_cls
	mov dh,0
	mov dl,35
	call vt_gotoxy
	lea dx,str1
	call vt_write_dos_str
	xor ax,ax
cic:
	mov ax,word ptr vv
	xor dx,dx
	mov bx,100
	mul bx
	mov bx,300
	div bx
	push dx
	xor dx,dx
        call vt_gotoxy
	push ax
	pop dx
	call vt_write_decimal
	push dx
	pop ax
	xor dx,dx
	mov bx,20
	mul bx
	mov bx,100
	div bx
	mov cx,ax
	cmp cx,0
	je lab
	mov dh,0
	mov dl,35
	call vt_gotoxy
cic2:
	mov dl,'�'
	call vt_write_char
	loop cic2
lab:
	pop dx
	mov ax,word ptr vv
	inc ax
	mov word ptr vv,ax
	cmp ax,300
	jl cic
	int 20h
	include vt.asm
code		ends
	end start
