code            segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
msg:    db'Iaza Formatter v 1.00 by Iaza Soft 1991(c).',10,13,'$'
msg1:   db'Formatting Track .. Side .',10,'$'
drive:  db 0
track:  db 39
side:   db 0
secpertrack:    db 9
curtrack:       db 0
curside:        db 0
ses:    dw 0
sbx:    dw 0
dtp:    db 11 dup(0)
ft:     db 30 dup(1,2,3,4)
boot:   db 256 dup(55h,0AAh)
setdtp:
	mov al,byte ptr track
	cmp al,0
	je globaltable
	mov al,byte ptr secpertrack
	cmp al,0
	jne localtable
globaltable:
	mov dl,byte ptr drive
	mov ah,8
	int 13h
	mov byte ptr track,ch
	mov byte ptr secpertrack,cl
	mov byte ptr side,dh

	jmp fine_setdtp
localtable:
	mov ah,18h
	mov ch,byte ptr track
	mov cl,byte ptr secpertrack
	mov dl,byte ptr drive
	int 13h

fine_setdtp:
	push di
	pop si
	lea dx,dtp
	push es
	pop ds
	push cs
	pop es
	push dx
	pop di
	mov cx,11
	rep movsb
	push cs
	pop ds
	mov ah,35h
	mov al,1eh
	int 21h
	mov word ptr sbx,bx
	push es
	pop ax
	mov word ptr ses,ax
	lea dx,dtp
	mov al,1eh
	mov ah,25h
	int 21h

	ret
format:
	push ax
	push bx
	push cx
	push dx
	push es
	push ds
	xor cl,cl
	mov ch,byte ptr secpertrack
	inc ch
	lea ax,ft
cic:
	mov byte ptr al,bl
	inc al
	mov byte ptr al,bh
	inc al
	inc cl
	mov byte ptr al,cl
	dec cl
	inc al
	mov byte ptr al,2
	inc cl
	cmp cl,ch
	jne cic
	push cs
	pop es
	mov dh,bh
	mov dl,byte ptr drive
	mov ch,bl
	mov cl,1
	lea bx,ft
	mov al,byte ptr secpertrack
	mov ah,5
	int 13h

	pop ds
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	ret
disk_reset:
	xor ah,ah
	xor dl,dl
	or dl,128
	int 13h
	ret
iniz:
	lea dx,msg
	mov ah,9
	int 21h
	call disk_reset
	mov ah,17h
	mov al,2
	mov dl,0
	int 13h
	call setdtp
	xor bx,bx
	mov dl,byte ptr track
	mov dh,byte ptr side
	inc dl
	inc dh
cic2:
	call format
	inc bh
	cmp bh,dh
	jne cic2
	xor bh,bh
	dec bl
	cmp bl,dl
	jne cic2

	mov bx,word ptr sbx
	mov ax,word ptr ses
	push ax
	pop ds
	mov ah,25h
	mov al,1eh
	int 21h
	push cs
	pop ds
	call disk_reset
	int 20h
code            ends
	end start
