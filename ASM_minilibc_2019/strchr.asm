BITS 64
section .text

GLOBAL strchr

strchr:
    push rbp
    mov rbp, rsp

    mov rax, 0
    cmp rdi, 0
    je strchr_bad_end
    jmp strchr_start

strchr_start:
    cmp BYTE [rdi], 0
    je strchr_bad_end
    cmp sil, [rdi]
    je strchr_good_end
    add rdi, 1
    jmp strchr_start

strchr_bad_end:
    leave
    ret

strchr_good_end:
    mov rax, rdi
    leave
    ret