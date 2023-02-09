BITS 64
section .text

GLOBAL rindex

rindex:
    push rbp
    mov rbp, rsp

    mov rax, 0
    cmp rdi, 0
    je rindex_end
    jmp rindex_start

rindex_start:
    cmp BYTE [rdi], 0
    je rindex_end
    cmp [rdi], sil
    je stock_index
    add rdi, 1
    jmp rindex_start

stock_index:
    mov rax, rdi

rindex_end:
    leave
    ret