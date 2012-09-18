 assume cs:code,ds:data,ss:stk       


data            segment
msg1	db 'pp$'
msg    db'Questo Š un EXE file $'
data            ends


code            segment
	include vtx.asm
start:
	mov ax,data
	mov ds,ax
	mov ax,stk
	mov ss,ax
	lea ax,ss:endss
	mov sp,ax
	mov dx,offset msg
	call vt_write_dos_str
	mov ah,4ch
	int 21h
code            ends


stk             segment
db 10 dup(0,0)
endss dw 0
stk             ends
	end start
