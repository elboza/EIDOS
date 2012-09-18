code            segment
        assume cs:code,ds:code
        org 100h
start:
        mov ax,offset iniz
        push ax
        ret
part:   db 512 dup(0)
        db 0
nome:   db 'd:\part.sec',0
hand:   dw 0
iniz:
        push ds
        pop es
        mov ah,2
        mov al,1
        mov bx,offset part
        xor ch,ch
        mov cl,1
        mov dh,0
        mov dl,80h
        int 13h
        lea dx,part
        call vt_write_str
        mov ah,3ch
        mov cx,20h
        lea dx,nome
        int 21h
        mov word ptr hand,ax
        mov bx,ax
        mov ah,40h
        mov cx,512
        lea dx,part
        int 21h
        mov bx,word ptr hand
        mov ah,3eh
        int 21h
        int 20h
        include vt.asm
code            ends
        end start

