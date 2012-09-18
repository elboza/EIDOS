code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint1c	proc	near
	push ax
	push bx
	push cx
	push dx
	push si
	mov ah,3
	mov bh,0
	int 10h
	mov byte ptr x,dh
	mov byte ptr y,dl
	mov dh,2
	mov dl,73
	mov byte ptr ix,dl
	mov bh,0
	mov ah,2
	int 10h
	mov ah,2
	int 1ah
	mov byte ptr ore,ch
	mov byte ptr min,cl
	mov al,ch
	call stampa
	mov ah,9
	mov al,':'
	mov cx,1
	mov bx,1eh
	or bl,128
	int 10h
	call cur_right
	mov al,byte ptr min
	call stampa
	mov ah,2
	mov bh,0
	mov dl,byte ptr y
	mov dh,byte ptr x
	int 10h
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	db 0eah
l1:	db 0,0
l2:	db 0,0
ore:	db 0
min:	db 0
x:	db 0
y:	db 0
ix:	db 73
stampa:	xor ah,ah
	mov si,16
	xor dx,dx
	div si
	push dx
	xor dx,dx
	div si
	push dx
	pop ax
	add al,30h
	mov ah,9
	mov cx,1
	mov bx,1eh
	int 10h
	call cur_right
	pop ax
	add al,30h
	mov ah,9
	int 10h
	call cur_right
	ret
cur_right:
        mov ch,byte ptr ix
	inc ch
	mov byte ptr ix,ch
	xor ch,ch
	push ax
	push bx
	push dx
	mov ah,2
	mov dh,2
	mov dl,byte ptr ix
	mov bh,0
	int 10h
	pop dx
	pop bx
	pop ax
	ret
nuovoint1c		endp
finepr label byte
msg:	db'Times version 1.00 by Iaza Soft 1990(c).$'
iniz:
	mov ah,9
	mov dx,offset msg
	int 21h
	mov ah,35h
	mov al,1ch
	int 21h
	mov word ptr l1,bx
	mov word ptr l2,es
	push cs
	pop ds
	mov dx,offset nuovoint1c
	mov ah,25h
	mov al,1ch
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
