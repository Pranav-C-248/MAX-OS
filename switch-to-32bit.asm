[bits 16]

section .data
    entry  db 'entering 32 bit mode' ,0

switch_to_32bit:
    mov bx,entry
    call print_string
    cli                     ; 1. disable interrupts
    lgdt [gdt_descriptor]   ; 2. load GDT descriptor
    mov eax, cr0
    or eax, 0x1             ; 3. enable protected mode
    mov cr0, eax
    jmp CODE_SEG:init_32bit ; 4. far jump

[bits 32]
init_32bit:
    mov ax, DATA_SEG        ; 5. update segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000        ; 6. setup stack
    mov esp, ebp

    call begin_32_bit       ; 7. move back to mbr.asm


