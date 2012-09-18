code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint9	proc	near
	push ax
	push bx
	push cx
	push dx
	push ds
	push si
	push cs
	pop ds
	in al,60h
	cmp al,33
	jne go_away
	mov ah,2
	int 16h
	test al,6
	jz go_away
	mov ah,3ch
	mov cx,20h
	lea dx,nome
	int 21h
	mov word ptr hand,ax
	xchg ax,bx
	mov ax,0b800h
	mov ds,ax
	mov ah,40h
	mov cx,8192
	xor dx,dx
	int 21h
	push cs
	pop ds
	cmp ax,cx
	je close

close:
	mov ah,3eh
	mov bx,word ptr hand
	int 21h
	mov bl,byte ptr count
	xor ah,ah
	mov al,6
	lea dx,nome
	add ax,dx
	inc bl
	cmp bl,255
	jne cjn
	xor bh,bh
cjn:
	mov byte ptr count,bl
	mov si,16
	xor dx,dx
	xchg ax,bx
	xor ah,ah
	div si
	add al,30h
	mov ds:byte ptr bx,ax
	add dl,30h
	inc bx
	mov dh,2eh
	mov ds:byte ptr bx,dx
go_away:
	pop si
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	db 0eah
l1:	db 0,0
l2:	db 0,0
nome:	db'c:\fwt00.bkg',0
hand:	dw 0
count:	db 0
nuovoint9		endp
ric:	db'Iaza Snap'
finepr label byte
msg:	db'Snap v 1.1 by Iaza Soft for Elfabio',"'",'s FWT.$'
iniz:
	mov ah,9
	mov dx,offset msg
	int 21h
	mov ah,35h
	mov al,9h
	int 21h
	mov word ptr l1,bx
	mov word ptr l2,es
	mov ax,es
	mov ds,ax
	push cs
	pop es
	mov di,offset ric
	mov si,di
	mov cx,9
	repe cmpsb
	jz exit
	push cs
	pop ds
	mov dx,offset nuovoint9
	mov ah,25h
	mov al,9h
	int 21h
	push cs
	pop es
	mov es,es:[2ch]
	mov ah,49h
	int 21h
	lea dx,finepr
	int 27h
exit:
	mov ah,9
	push cs
	pop ds
	mov dx,offset ext
	int 21h
	int 20h
ext:	db 13,10,'Programma gi… installato in memoria.$'
code		ends
	end start
