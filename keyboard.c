#include "isr.h"
#include "screen_driver.h"
#include "keyboard.h"
#include "util.h"
#include "shell.h"



static char key_buffer[256];

const char scancode_to_char[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    
    if(scancode>MAX_SCANCODE)return;

    if(scancode==BACKSPACE){
        int cur_len=string_length(key_buffer);

        if(cur_len>0){
            key_buffer[cur_len-1]='\0';
            int offset=get_cursor()-2;
            print_char(' ',offset);
            set_cursor(offset);
            // print_string("BACKSPACE");

        }
    }
    else if(scancode==ENTER){
        int cur_len=string_length(key_buffer);
        if(cur_len==0){
            print_string("\n>");
        }
        parse_command(key_buffer);
        key_buffer[0]='\0';
    }
    else{
        int cur_len=string_length(key_buffer);
        char typed_char=scancode_to_char[(int)scancode];
        append(typed_char,key_buffer);
        cur_len+=1;
        char str[2]={typed_char,'\0'};
        print_string(str);
    }
}

void init_keyboard(){
    install_interrupt_handler(33,keyboard_callback);
}

