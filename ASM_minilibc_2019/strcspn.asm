BITS 64
section .text

GLOBAL strcspn

strcspn:
    mov rcx, 0
    cmp rdi, 0
    je strcspn_end
    cmp [rdi], byte 0
    je strcspn_end
    mov r9b, 0
    mov rax, 0
    mov rdx, 0
    mov r9, rsi

strcspn_loop:
    mov r9b, byte [rsi + rdx]
    mov al, [rdi + rcx]
    cmp al, r9b
    je strcspn_end
    cmp r9b, byte 0
    je strcspn_init
    inc rdx
    jmp strcspn_loop

strcspn_init:
    inc rcx
    mov rdx, 0
    jmp strcspn_loop

strcspn_end:
    mov rax, rcx
    ret