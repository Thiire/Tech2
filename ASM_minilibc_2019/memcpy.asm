BITS 64
section .text

GLOBAL memcpy

memcpy:
    push rbp
    mov rbp, rsp

    mov rax, rdi
    jmp memcpy_start

memcpy_start:
    cmp edx, 0
    je memcpy_end
    mov r8b, BYTE [rsi]
    mov [rdi], r8b
    inc rdi
    inc rsi
    dec edx

memcpy_end:
    leave
    ret
