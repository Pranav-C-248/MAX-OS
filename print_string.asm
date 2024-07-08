
;print_string
;bx stores the address to the msg. loop to all chars putting each in al.

print_string:
    pusha

    .loop:
        mov al,[bx]
        cmp al,0
        je .done
        mov ah,0x0e   ;teletype
        int 0x10 
        inc bx
        jmp .loop

    .done:
        popa
        ret

