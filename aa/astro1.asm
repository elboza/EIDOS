code		segment
	assume cs:code,ds:code
	org 100h
start:
	mov ax,offset iniz
	push ax
	ret
dimx:	db 3
dimy:	db 1
fis:	db'®è¯'

iniz:
	mov al,3
	mov byte ptr vd1,al
	mov al,1
	mov byte ptr vd2,al
	mov dh,10
	mov dl,10
	call put
	int 20h
put:
;----------------------------------------------------------------------------;
;	Visualizza l'astronave						     ;
;									     ;
;	DH : coordinata x						     ;
;	DL : coordinata y						     ;
;----------------------------------------------------------------------------;
	push ax
	push bx
	push cx
	push dx
	mov ax,dx
	mov byte ptr x1,ah
	mov byte ptr y1,al
	xor bh,bh
	mov bl,15
	mov cx,3
	push ds
	pop es
	lea ax,fis
	mov bp,ax
	mov al,0
	mov ah,13h
	int 10h
	pop dx
	pop cx
	pop bx
	pop ax
	ret
x1:     db 0
y1:	db 0
vd1:	db 0
vd2:	db 0
;--end put--;
code		ends
	end start
