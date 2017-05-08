.intel_syntax noprefix
.data
msg:
    .string "hello c\n"

.text
.globl _start
_start:
    mov eax, 4
    mov ebx, 1
    lea ecx, [msg]
    mov edx, 8
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80
