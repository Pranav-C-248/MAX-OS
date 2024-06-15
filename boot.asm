;*********************************************
;	boot.asm
;		- A Simple Bootloader
;*********************************************
 
org		0x7c00				; We are loaded by BIOS at 0x7C00
bits	16					; We are still in 16 bit Real Mode



KERNEL_OFFSET equ 0x1000

;dl stores drive number , store it in another variable
mov [BOOT_DRIVE],dl

;set up the stack to the far side
mov bp, 0x9000
mov sp,bp

call load_kernel 	;this loads kernel into memory
call switch_to_32bit 	; this initiates pm mode

%include "print_string_16.asm"
%include "disk.asm"
%include "gdt.asm"
%include "switch-to-32bit.asm"

jmp $				;loop incase returns

[bits 16]
load_kernel :
	mov bx,[KERNEL_OFFSET]
	mov dl,[BOOT_DRIVE]		;which drive to read from
	mov dh,2 				;which sector to read
	call disk_load 
	ret

[bits 32]
begin_32_bit:
	call KERNEL_OFFSET ;giving control to kernel which is at kernel offset location
	jmp $			   ; failsafe incase it returns


; boot drive variable
BOOT_DRIVE db 0
	
times 510 - ($-$$) db 0				; We have to be 512 bytes. Clear the rest of the bytes with 0
 
dw 0xAA55		; 