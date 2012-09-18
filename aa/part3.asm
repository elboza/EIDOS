code            segment
        assume cs:code,ds:code
        org 100h
start:
        mov ax,offset iniz
        push ax
        ret
iniz:
        push ds
        pop es
        mov ah,3
        mov al,1
        mov bx,offset mycode
        mov ch,00011110b
        mov cl,10001100b
        mov dh,3
        mov dl,80h
        int 13h
        int 20h
org 7e00h
mycode: 
        push cs
        pop ds
        call cls
        mov ah,13h
        mov al,0
        mov bx,4
        mov cx,31
        mov dh,3
        mov dl,3
        push cs
        pop es
        mov bp,offset msg
        int 10h
        mov ah,2
        mov bh,0
        mov dl,14
        mov dh,14
        int 10h
        mov bx,offset buff
        mov cx,bx
        push bx
cic:
        mov ah,0
        int 16h
        pop bx
        cmp al,13
        je finecic
        db 88h,7
        inc bx
        push bx
        mov ah,0ah
        mov al,2eh
        push cx
        mov cx,1
        push bx
        mov bh,0
        mov bl,04
        int 10h
        mov ah,2
        mov bh,0
        mov dh,14
        mov dl,byte ptr xx
        inc dl
        mov byte ptr xx,dl
        int 10h
        pop bx
        pop cx
        jmp cic
finecic:
        sub bx,cx
        mov cx,bx
        mov byte ptr lung,cl
        push cs
        pop es
        push cs
        pop ds
        mov di,offset buff
        mov si,offset norm
        repe cmpsb
        je cnorm
        mov cl,byte ptr lung
        xor ch,ch
        mov bx,offset buff
cic2:
        db 8ah,7
        xor al,0ffh
        db 88h,7
        inc bx
        loop cic2
        mov cl,byte ptr lung
        mov di,offset buff
        mov si,offset cry
        repe cmpsb
        je ccry
        db 0eah,0,7ch,0,0
cnorm:     
        mov al,2
        db 0a2h,0d2h,7dh
        jmp restore
ccry:
        mov al,5
        db 0a2h,0d2h,7dh
restore:        
        xor ax,ax
        push ax
        pop es
        mov ah,3
        mov al,1
        mov ch,0
        mov cl,1
        xor dh,dh
        mov dl,80h
        mov bx,7c00h
        int 13h
        mov al,0fah
        db 0a2h,00,7ch
        mov al,33h
        db 0a2h,1,7ch
        mov al,0c0h
        db 0a2h,2,7ch
        db 0eah,00,7ch,00,00
cls:    mov ah,6
        xor al,al
        mov bh,04h
        xor cx,cx
        mov dh,40
        mov dl,40
        int 10h
        ret
msg:    db'Please enter authorization code :'
norm:   db 'normal',0,0
cry:    db 93h,8ah,8fh,96h,91h,0,0,0
buff:   db 8 dup(0)
lung:   db 0
xx:     db 14
endmy:  db 0        
code            ends
        end start

