BITS 64
section .text

GLOBAL strpbrk

strpbrk:
    cmp rsi, 0
    je strpbrk_error 
    cmp [rsi], byte 0
    je strpbrk_error
    cmp rdi, 0
    je strpbrk_error
    cmp [rdi], byte 0
    je strpbrk_error
    mov r9b, 0
    mov rax, 0
    mov rdx, 0

strpbrk_loop:
    mov r9b, byte [rsi + rdx]
    mov al, [rdi]
    cmp al, r9b
    je strpbrk_end
    inc rdx
    cmp r9b, byte 0
    je strpbrk_init
    jmp strpbrk_loop

strpbrk_init:
    inc rdi
    mov rdx, 0
    cmp [rdi], byte 0
    je strpbrk_error
    jmp strpbrk_loop

strpbrk_end:
    mov rax, rdi
    ret

strpbrk_error:
    mov rax, 0
    ret