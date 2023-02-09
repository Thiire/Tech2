BITS 64
section .text

GLOBAL memmove

memmove:
	mov rcx, 0

memmove_start:
	cmp rdx, rcx
	jle memmove_loop
 	mov r10b, byte [rsi + rcx]
 	mov [rdi], r10b
	inc rdi
	inc rcx
	jmp memmove_start

memmove_loop:
	cmp rcx, 0
	je memmove_end
	dec rdi
	dec rcx
	jmp memmove_loop

memmove_end:
	mov rax, rdi
	ret