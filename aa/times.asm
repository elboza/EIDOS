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
	push ds
	push es
	push si
	push cs
	pop ds
	mov ah,2
	int 1ah
	mov byte ptr ore,ch
	mov byte ptr min,cl
	mov byte ptr sec,dh
	mov ah,byte ptr aore
	mov al,byte ptr ore
	cmp ah,al
	jne c_video
	mov ah,byte ptr amin
	mov al,byte ptr min
	cmp ah,al
	jne c_video
	mov al,byte ptr flags
	test al,1
	jnz c_video
	mov ah,0eh
	mov al,7
	int 10h
c_video:
	xor ax,ax
	mov es,ax
	mov bx,449h
	mov al,es:byte ptr bx
	cmp al,4
	jl cont
	jmp exit_1ch
cont:
	mov ax,40h
	mov es,ax
	mov ah,byte ptr y
	mov al,es:byte ptr 84h
	mov byte ptr maxy,al
	cmp ah,al
	jl cint
	mov byte ptr y,al
cint:
	mov ax,0b800h
	push ax
	pop es
	mov bx,80
	xor dx,dx
	mov al,byte ptr y
	xor ah,ah
	mul bx
	mov bl,byte ptr x
	xor bh,bh
	add ax,bx
	mov bx,2
	mul bx
	mov word ptr loc,ax
	mov word ptr loc2,ax
	mov al,byte ptr flags
	test al,2
	jz cont2
	call get
	jmp exit_1ch
cont2:
	mov bx,word ptr loc
	mov ax,0
	mov al,es:byte ptr bx
	cmp al,'{'
	jne c_get
	add bx,12
	mov al,es:byte ptr bx
	cmp al,'}'
	je no_get
c_get:	call get
no_get:	mov bx,word ptr loc
	mov ah,byte ptr color
	mov al,'{'
	mov es:word ptr bx,ax
	call cur_right
	mov al,byte ptr ore
	call stampa
	mov ah,0
	xor dx,dx
	mov al,byte ptr sec
	mov bx,2
	div bx
	mov al,32
	cmp dx,0
	je fif
	mov al,':'
fif:
	mov ah,byte ptr color
	mov bx,word ptr loc
	mov es:word ptr bx,ax
	call cur_right
	mov al,byte ptr min
	call stampa
	mov bx,word ptr loc
	mov ah,byte ptr color
	mov al,'}'
	mov es:word ptr bx,ax
exit_1ch:
	pop si
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	db 0eah
l1:	db 0,0
l2:	db 0,0
ore:	db 0
min:	db 0
x:	db 73
y:	db 2
loc:	dw 0
color:	db 1eh
aore:	db 0
amin:	db 0
sec:	db 0
flags:	db 0
flags2:	db 0
loc2:	dw 0
sotto:	dw 0,0,0,0,0,0,0,0
maxx:	db 73
maxy:	db 24
vex:	db 0
vey:	db 0
als:	dw 0,0,0,0,0,0,0,0
varcount:db 0
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
	mov ah,byte ptr color
	mov bx,word ptr loc
	mov es:word ptr bx,ax
	call cur_right
	pop ax
	add al,30h
	mov ah,byte ptr color
	mov bx,word ptr loc
	mov es:word ptr bx,ax
	call cur_right
	ret
cur_right:
	inc bx
	inc bx
	mov word ptr loc,bx
	ret
nuovoint1c		endp
nuovoint9	proc	near
	push ax
	push bx
	push cx
	push dx
	push ds
	push cs
	pop ds
	in al,60h
	mov ah,byte ptr flags2
	test ah,1
	jnz hg
	jmp noset
hg:
	mov ah,al
	xor al,al
	out 60h,al
	mov al,ah
	cmp al,1
	jnl cont_test
	jmp go_away
cont_test:
	cmp al,12
	jl contest2
	jmp go_away
contest2:
	dec al
	cmp al,10
	jne contset
	mov al,0
contset:
	mov ah,byte ptr varcount
	cmp ah,0
	jne ne1
	call putvar
	mov cl,4
	shl al,cl
	mov byte ptr aore,al
	inc ah
	mov byte ptr varcount,ah
	jmp go_away
ne1:
	cmp ah,1
	jne ne2
	mov bl,byte ptr aore
	add bl,al
	mov byte ptr aore,bl
	inc ah
	mov byte ptr varcount,ah
	call putvar
	call setcurr
	jmp go_away
ne2:
	cmp ah,2
	jne ne3
	call putvar
	mov cl,4
	shl al,cl
	mov byte ptr amin,al
	inc ah
	mov byte ptr varcount,ah
	jmp go_away
ne3:
	mov bl,byte ptr amin
	add bl,al
	mov byte ptr amin,bl
	xor ah,ah
	mov byte ptr varcount,ah
	mov al,byte ptr flags2
	xor al,al
	mov byte ptr flags2,al
	call putvar
	mov dh,12
	mov dl,25
	mov bh,0
	mov ah,2
	int 10h

	mov dx,0
ccic:
	xchg bx,dx
	mov ax,word ptr als[bx]
	xchg bx,dx
	mov bl,ah
	mov ah,9
	xor bh,bh
	mov cx,1
	int 10h
	inc dx
	inc dx
	call setcurr
	cmp dx,14
	jne ccic
	mov dh,byte ptr vey
	mov dl,byte ptr vex
	mov ah,2
	xor bh,bh
	int 10h
	jmp go_away

noset:
	cmp al,78;plus
	jne meno
	mov ah,2
	int 16h
	test al,8;alt
	jz plus2
	mov ah,al
	mov al,byte ptr color
	add al,10h
	mov byte ptr color,al
	mov al,ah
plus2:
	test al,4;ctrl
	jnz p2ok
	jmp go_away
p2ok:
	mov al,byte ptr color
	mov ah,al
	and ah,0fh
	cmp ah,0fh
	jne ok1
	sub al,10h
ok1:	inc al
	mov byte ptr color,al
	jmp go_away
meno:
	cmp al,74
	jne all_off
	mov ah,2
	int 16h
	test al,8
	jz meno2
	mov ah,al
	mov al,byte ptr color
	sub al,10h
	mov byte ptr color,al
	mov al,ah
meno2:
	test al,4
	jnz nemo2ok2
	jmp go_away
nemo2ok2:
	mov al,byte ptr color
	mov ah,al
	and ah,0fh
	cmp ah,0
	jne ok2
	add al,10h
ok2:	dec al
	mov byte ptr color,al
	jmp go_away
all_off:
	cmp al,82;ins
	jne alt_esc
	mov ah,2
	int 16h
	test al,4
	jnz all_cont
	jmp go_away
all_cont:
	mov al,byte ptr flags
	and al,0feh
	mov byte ptr flags,al
	jmp go_away
alt_esc:
	cmp al,1
	jne ctrl_4
	mov ah,2
	int 16h
	test al,8
	jnz a_e
	jmp go_away
a_e:
	mov al,byte ptr flags
	xor al,2
	mov byte ptr flags,al
	call put
	jmp go_away
ctrl_4:
	cmp al,75
	jne ctrl_6
	mov ah,2
	int 16h
	test al,4
	jnz cc4
	jmp go_away
cc4:
	mov bh,byte ptr x
	cmp bh,0
	jne ccc4
	jmp go_away
ccc4:
	dec bh
	call put
	mov byte ptr x,bh
	jmp go_away
ctrl_6:
	cmp al,77
	jne ctrl_8
	mov ah,2
	int 16h
	test al,4
	jnz cc6
	jmp go_away
cc6:	mov bh,byte ptr x
	cmp bh,73
	jne ccc6
	jmp go_away
ccc6:	inc bh
	call put
	mov byte ptr x,bh
	jmp go_away
ctrl_8:
	cmp al,72
	jne ctrl_2
	mov ah,2
	int 16h
	test al,4
	jnz cc8
	jmp go_away
cc8:	mov bh,byte ptr y
	cmp bh,0
	jne ccc8
	jmp go_away
ccc8:	dec bh
	call put
	mov byte ptr y,bh
	jmp go_away
ctrl_2:
	cmp al,80
	jne ctrl_9
	mov ah,2
	int 16h
	test al,4
	jnz cc2
	jmp go_away
cc2:	mov bh,byte ptr y
	cmp bh,79
	jne ccc2
	jmp go_away
ccc2:	inc bh
	call put
	mov byte ptr y,bh
	jmp go_away
ctrl_9:
	cmp al,73
	jne ctrl_7
	mov ah,2
	int 16h
	test al,4
	jnz cc9
	jmp go_away
cc9:	call put
	mov ah,73
	mov al,0
	mov byte ptr x,ah
	mov byte ptr y,al
	jmp go_away
ctrl_7:
	cmp al,71
	jne ctrl_1
	mov ah,2
	int 16h
	test al,4
	jnz cc7
	jmp go_away
cc7:	call put
	xor ax,ax
	mov byte ptr x,ah
	mov byte ptr y,al
	jmp go_away
ctrl_1:
	cmp al,79
	jne ctrl_3
	mov ah,2
	int 16h
	test al,4
	jnz cc_1
	jmp go_away
cc_1:	call put
	xor ah,ah
	mov al,byte ptr maxy
	mov byte ptr x,ah
	mov byte ptr y,al
	jmp go_away
ctrl_3:
	cmp al,81
	jne ctrl_canc
	mov ah,2
	int 16h
	test al,4
	jnz cc3
	jmp go_away
cc3:
	call put
	mov ah,73
	mov al,byte ptr maxy
	mov byte ptr x,ah
	mov byte ptr y,al
	jmp go_away
ctrl_canc:
	cmp al,83
	jne ctrl_t
	mov ah,2
	int 16h
	test al,4
	jnz ccanc
	jmp go_away
ccanc:
	mov al,byte ptr flags
	or al,1
	mov byte ptr flags,al
	jmp go_away
ctrl_t:
	cmp al,20
	je ccrtt1
	jmp go_away
ccrtt1:
	mov ah,2
	int 16h
	test al,4
	jnz ccrtt2
	jmp go_away
ccrtt2:
	xor al,al
	out 60h,al
	mov al,byte ptr flags2
	or al,1
	mov byte ptr flags2,al
	mov ah,3
	mov bh,0
	int 10h
	mov byte ptr vex,dl
	mov byte ptr vey,dh
	mov dh,12
	mov dl,25
	mov bh,0
	mov ah,2
	int 10h
	;fare get
	mov cx,7
	xor dx,dx
getcic:
	mov ah,8	;get char & att.
	xor bh,bh
	int 10h
	xchg bx,dx
	mov word ptr als[bx],ax
	xchg bx,dx
	inc dx
	inc dx
	call setcurr
	loop getcic
	mov dh,12
	mov dl,25
	mov bh,0
	mov ah,2
	int 10h
	mov ah,9
	mov al,' '
	xor bh,bh
	mov bl,70h
	mov cx,7
	int 10h
	mov cx,1
	mov ah,9
	mov al,'['
	mov bl,70h
	xor bh,bh
	int 10h
	call setcurr
	mov al,byte ptr aore
	call stp2
	mov ah,9
	xor bh,bh
	mov cx,1
	mov bl,70h
	mov al,':'
	int 10h
	call setcurr
	mov al,byte ptr amin
	call stp2
	mov ah,9
	mov al,']'
	xor bh,bh
	mov bl,70h
	mov cx,1
	int 10h
	mov dh,12
	mov dl,25
	mov bh,0
	mov ah,2
	int 10h
	jmp go_away
go_away:
	pop ds
	pop dx
	pop cx
	pop bx
	pop ax
	db 0eah
i91:	db 0,0
i92:	db 0,0
stp2:
	push ax
	push bx
	push cx
	push dx
	xor ah,ah
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
	xor bh,bh
	mov bl,70h
	mov cx,1
	int 10h
	call setcurr
	pop ax
	add al,30h
	mov ah,9
	mov bl,70h
	xor bh,bh
	mov cx,1
	int 10h
	call setcurr
	pop dx
	pop cx
	pop bx
	pop ax
	ret
put:
	push bx
	push cx
	push dx
	push es
	mov ax,0b800h
	mov es,ax
	mov bx,word ptr loc2
	lea dx,sotto
	mov cx,14
cic2:
	xchg bx,dx
	mov ax,ds:word ptr bx
	xchg dx,bx
	mov es:word ptr bx,ax
	dec cx
	inc bx
	inc bx
	inc dx
	inc dx
	loop cic2
	pop es
	pop dx
	pop cx
	pop bx
	ret

get:    push ax
	push bx
	push cx
	push dx
	push es
	mov ax,0b800h
	mov es,ax
	mov bx,word ptr loc2
	mov cx,14
	lea dx,sotto
cic:	mov ax,es:word ptr bx
	xchg dx,bx
	mov ds:word ptr bx,ax
	xchg bx,dx
	inc dx
	dec cx
	inc dx
	inc bx
	inc bx
	loop cic
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret
putvar:
	push ax
	push bx
	push cx
	push dx
	add al,30h
	mov ah,9
	xor bh,bh
	mov bl,70h
	mov cx,1
	int 10h
	pop dx
	pop cx
	pop bx
	pop ax
	call setcurr
	ret
setcurr:
	push ax
	push bx
	push cx
	push dx
	mov ah,3
	xor bh,bh
	int 10h
	inc dl
	xor bh,bh
	mov ah,2
	int 10h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
nuovoint9		endp
ric:	db'Iaza Times'
finepr label byte
msg:	db'Times version 1.8 by Iaza Soft 1990(c).$'
iniz:
	mov ah,9
	mov dx,offset msg
	int 21h
	mov ah,35h
	mov al,1ch
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
	push cs
	pop ds
	mov dx,offset nuovoint1c
	mov ah,25h
	mov al,1ch
	int 21h
	mov ah,35h
	mov al,9
	int 21h
	mov word ptr i91,bx
	mov word ptr i92,es
	mov ah,25h
	mov al,9
	mov dx,offset nuovoint9
	int 21h
	push cs
	pop es
	mov es,es:[2ch]
	mov ah,49h
	int 21h
	lea dx,finepr
	int 27h
exit:	mov ah,9
	push cs
	pop ds
	mov dx,offset ext
	int 21h
	int 20h
ext:	db 10,13,'Programma gi… installato in memoria$'
code		ends
	end start
