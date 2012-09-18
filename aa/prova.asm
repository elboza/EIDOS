assume cs:code,ds:data,ss:stk
data		segment
msg	db'Ciao',10,13,' $'
iniz	db 90h
	push cs
	pop ds
	lea dx,msg
	mov ah,9
	int 21h
	mov ah,4ch
	int 21h
data		ends

code		segment
include vtx.asm
start:
	mov ax,data
	mov ds,ax
	mov ax,stk
	mov ss,ax
	lea ax,ss:endss
	mov sp,ax
	push ds
	lea ax,iniz
	push ax
	retf
code		ends

stk		segment
	db 20 dup (0)
endss	db 0
stk		ends
	end start
