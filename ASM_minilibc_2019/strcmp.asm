BITS 64
section .text

GLOBAL strcmp

strcmp:
    push rbp
    mov rbp, rsp

    cmp rdi, 0
    je strcmp_null
    cmp rsi, 0
    je strcmp_null
    mov rax, 0
    jmp strcmp_start

strcmp_start:
    cmp BYTE [rdi], 0
    je strcmp_end
    cmp BYTE [rsi], 0
    je strcmp_end
    mov r8b, BYTE [rdi]
    cmp [rsi], r8b
    jne strcmp_end
    inc rsi
    inc rdi
    jmp strcmp_start

strcmp_end:
    mov al, [rsi]
    sub al, [rdi]
    leave
    ret

strcmp_null:
    mov rax, -1
    ret
