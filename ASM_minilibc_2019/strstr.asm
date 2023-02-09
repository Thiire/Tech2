BITS 64
section .text

GLOBAL strstr

strstr:
    cmp rdi, 0
    je strstr_error
    cmp [rdi], byte 0
    je strstr_error
    mov r11, rdi
    mov r10b, 0
    mov rdx, 0

strstr_loop:
    mov r10b, byte [rsi + rdx]
    cmp r10b, byte 0
    je strstr_end
    cmp r10b, [r11]
    jne strstr_init
    inc rdx
    inc r11
    jmp strstr_loop

strstr_init:
    mov rdx, 0
    inc rdi
    cmp [rdi], byte 0
    je strstr_error
    mov r11, rdi
    jmp strstr_loop

strstr_end:
    mov rax, rdi
    ret

strstr_error:
    mov rax, 0
    ret