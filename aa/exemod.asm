code            segment
        assume cs:code,ds:code
        org 100h
start:
        mov ax,offset iniz
        push ax
	ret
nomex:  db 80,0
nome:	db 80 dup(0)
msg1:   db 'Nome del file .EXE-->$'
hh:     dw 0
sig:	db'Exemod v 1.00 (c) 1991, by Iaza Soft',10,13,'$'
buff:   db 512 dup(0)
msg2:   db 10,13,'Exe signature :$'
msg3:   db'Lenth of image :$'
msg32:	db'Size of file + heather :$'
msg4:   db'Number of relocation items :$'
msg5:   db 'Size of header :$'
msg6:   db 'Minimum number of paragraphs :$'
msg7:   db 'Maximum number of paragraphs :$'
msg8:   db 'SS :$'
msg9:   db 'SP :$'
msg10:  db 'word checksum :$'
msg11:  db 'IP :$'
msg12:  db 'CS :$'
msg13:  db 'Displacement of first relocation table :$'
msg14:  db 'Overlay number :$'
iniz:
	mov ah,9
	mov dx,offset sig
	int 21h
	mov ah,9
	lea dx,msg1
	int 21h
	mov ah,0ah
	lea dx,nomex
	int 21h
	lea bx,nomex
	inc bx
	mov dl,[bx]
	xor dh,dh
	add bx,dx
	inc bx
	xor dx,dx
	mov [bx],dx
	mov ah,3dh
	mov al,0
	lea dx,nome
	int 21h
	mov word ptr hh,ax
	mov bx,ax
	mov ah,3fh
	mov cx,512
	mov dx,offset buff
	int 21h
	mov ah,3eh
	mov bx,word ptr hh
	int 21h
	mov dx,offset msg2
	call vt_write_dos_str
	mov bx,offset buff
	mov dl,[bx]
	mov ah,2
	int 21h
	inc bx
	mov dl,[bx]
	mov ah,2
	int 21h
	call vt_send_crlf
	inc bx
	mov dx,offset msg3
	call vt_write_dos_str
	mov dx,[bx]
	inc bx
	inc bx
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg32
	call vt_write_dos_str
	mov dx,[bx]
	inc bx
	inc bx
	mov si,512
	mov ax,dx
	xor dx,dx
	mul si
	call vt_write_decimal
	mov dx,ax
	call vt_write_decimal
	call vt_send_crlf
	mov dx,offset msg4
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg5
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg6
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg7
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg8
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg9
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg10
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg11
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg12
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	lea dx,msg13
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	mov dx,offset msg14
	call vt_write_dos_str
	mov dx,[bx]
	add bx,2
	call vt_write_decimal
	call vt_send_crlf
	int 20h
	include vt.asm
code            ends
        end start

