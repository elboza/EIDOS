code		segment public
	assume cs:code,ds:code
	org 100h
start:
	call vt_font8x8
	mov dl,0fh
	call vt_write_hex_digit
	mov dx,1736
	call vt_write_decimal
	int 20h
	include vtx.asm
code		ends
	end start
