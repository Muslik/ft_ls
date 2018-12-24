/*
**  size_t  ft_strlen(const char *str);
**          |                     |
**          |                     V
**    %rax<-+                     %rdi
*/

.text
.global _ft_strlen

_ft_strlen:
    mov     %rdi, %rax
    mov     %rdi, %r11
    and     $0b111, %rax
    cmp     $0, %rax
    je      aligned
    mov     $8, %rcx
    sub     %rax, %rcx
    xor     %rax, %rax
    repne   scasb
    cmp     $0, %rcx
    jne     rtn
aligned:
    mov     $0x0101010101010101, %r8
    mov     $0x8080808080808080, %r9
loop:
    mov     (%rdi), %rdx
    sub     %r8, %rdx
    test    %r9, %rdx
    je      loop_inc
    mov     $8, %rcx
    repne   scasb
    cmp     $0, %rcx
    jne     rtn
    jmp     loop
loop_inc:
    add     $8, %rdi
    jmp     loop
rtn:
    sub     %r11, %rdi
    mov     %rdi, %rax
    dec     %rax
    ret
