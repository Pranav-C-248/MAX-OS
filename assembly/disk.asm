section .data
    DISK_ERROR db 'Disk Error', 0
    SECTOR_ERROR db 'Sector Error', 0

disk_load:
; reading from disk requires setting specific values in all registers
    ; so we will overwrite our input parameters from 'dx'. Let's save it
    ; to the stack for later use.
    pusha
    push dx

    mov ah, 0x02   ; read mode
    mov al, dh     ; read dh number of sectors
    mov cl, 0x02   ; start from sector 2 (sector 1 is the boot sector)
    mov ch, 0x00   ; cylinder 0
    mov dh, 0x00   ; head 0
    int 0x13       ; BIOS interrupt
    jc disk_error  ; check carry bit for error

    pop dx         ; restore original number of sectors to read
    cmp al, dh     ; compare actual sectors read (in al) with expected (in dh)
    jne sectors_error

    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print_string
    jmp $

sectors_error:
    mov bx, SECTOR_ERROR
    call print_string
    jmp $
