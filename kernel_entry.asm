[BITS 32]
[extern main]

section .text
global _start

_start:
    call main
    cli
    hlt
    jmp $
