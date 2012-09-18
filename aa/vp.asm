CODE SEGMENT
	ASSUME CS:CODE,DS:CODE,ES:CODE
	ORG 100h
start: JMP SHORT Installa
NuovoInt13  PROC NEAR
	    cmp ah,0ffh
	    jnz L1
	    mov ah,0feh
	    retf 2
L1:	    cmp dl,80h
	    jnb L2
	    jmp L3
L2:	    cmp ah,03h
	    jz L5
	    cmp ah,05h
	    jz L5
	    cmp ah,06h
	    jz L5
	    cmp ah,07h
	    jz L5
	    cmp ah,0bh
	    jz L5
	    cmp ah,0fh
	    jz L5
	    jmp L3
L5:	    stc
	    mov ah,03
	    retf 2
L3:         DB 0EAh
L01:        DB 00
L02:        DB 00
L03:        DB 00
L04:        DB 00
NuovoInt13  ENDP
Fine LABEL BYTE
ctr	proc	near
	mov ax,3513h
	int 21h
	mov cl,es:byte ptr bx
	cmp cl,80h
	jz iaz
	ret
iaz:
	mov ah,9
	mov dx,offset giainst
	int 21h
	int 20h
ctr		endp
Installa     PROC NEAR
	mov ax,offset iniz
	push ax
	ret
msg:	db'Write Protect Hard Disk, by Iaza Soft 1990(c).$'
giainst: db 10,13,'Programma gia',27h,' installato.$'
iniz:
	mov ah,9
	mov dx,offset msg
	int 21h
	call ctr
		mov ax,cs
		mov ds,ax
		mov ax,3513h
		int 21h
		mov WORD PTR L01,bx
		mov WORD PTR L03,es
		mov dx,OFFSET NuovoInt13
		mov ax,2513h
		int 21h
		mov es,es:[2ch]
		mov ah,49h
		int 21h
		lea dx,Fine
		int 27h
Installa ENDP
CODE     ENDS
	 END  start
