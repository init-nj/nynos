bits 64

section .text
global _start
extern kernel_main

_start:
    cli
    cld

    ; Align the stack for the x86-64 System V ABI.
    and rsp, -16

    ; Enter our C kernel.
    call kernel_main

.hang:
    hlt
    jmp .hang
