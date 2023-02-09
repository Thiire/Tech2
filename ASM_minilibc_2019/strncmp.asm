BITS 64
section .text

GLOBAL strncmp

strncmp:
    push rbp
    mov rbp, rsp

    mov r9d, 0
    mov rax, 0
    cmp rdi, 0
    je strncmp_end
    cmp rsi, 0
    je strncmp_end
    jmp strncmp_start

strncmp_start:
    cmp BYTE [rdi], 0
    je strncmp_end
    cmp BYTE [rsi], 0
    je strncmp_end
    cmp DWORD edx, DWORD r9d
    je strncmp_end
    mov r8b, BYTE [rdi]
    cmp [rsi], r8b
    jne strncmp_end
    inc rsi
    inc rdi
    inc r9d
    jmp strncmp_start

strncmp_end:
    mov al, [rdi]
    sub al, [rsi]
    leave
    ret
