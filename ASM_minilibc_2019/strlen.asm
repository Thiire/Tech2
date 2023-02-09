BITS 64
section .text

GLOBAL strlen

strlen:
    push rbp
    mov rbp, rsp

    mov rax, 0
    cmp rdi, 0
    je strlen_end
    jmp strlen_start

strlen_start:
    cmp BYTE [rdi + rax], 0
    je strlen_end
    add rax, 1
    jmp strlen_start

strlen_end:
    leave
    ret