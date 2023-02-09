BITS 64
section .text

GLOBAL memset

memset:
    push rbp
    mov rbp, rsp

    mov rax, rdi
    jmp memset_start

memset_start:
    cmp edx, 0
    je memset_end
    mov [rdi], sil
    inc rdi
    dec edx

memset_end:
    leave
    ret
