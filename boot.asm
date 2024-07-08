;*********************************************
;	boot.asm
;		- A Simple Bootloader
;*********************************************
[org 0x7c00]				; We are loaded by BIOS at 0x7C00
[bits 16]				; We are still in 16 bit Real Mode 


section .data
	s1 db 'loading to memory',0
	; s2 db 'now in 32 bit',0

KERNEL_OFFSET equ 0x1000

;dl stores drive number , store it in another variable
mov [BOOT_DRIVE],dl

;set up the stack to the far side
mov bp, 0x9000
mov sp,bp

call load_kernel 	;this loads kernel into memory
call switch_to_32bit 	; this initiates pm mode


jmp $				;loop incase returns

%include "assembly/print_string_16.asm"
%include "assembly/disk.asm"
%include "assembly/gdt.asm"
%include "assembly/switch-to-32bit.asm"


[bits 16]
load_kernel :
	mov bx,s1
	call print_string
	mov bx,KERNEL_OFFSET
	mov dl,[BOOT_DRIVE]		;which drive to read from
	mov dh,31			;which sector to read
	call disk_load 
	ret

[bits 32]
begin_32_bit:
	call KERNEL_OFFSET ;giving control to kernel which is at kernel offset location
	jmp $			   ; failsafe incase it returns


; boot drive variable
BOOT_DRIVE db 0
	
times 510 - ($-$$) db 0				; We have to be 512 bytes. Clear the rest of the bytes with 0
 
dw 0xaa55	
