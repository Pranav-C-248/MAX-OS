#include "util.h"
#include "screen_driver.h"
//#include "/Users/manaskumar/Desktop/MAX-OS-P1/main/tetris.h"
#include "keyboard.h"
#include "isr.h"
#include <stdint.h>
#include "port.h"
#include "shell.h"

#define KEYBOARD_DATA_PORT 0x60
#define MAX_SCANCODE 57
#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];
static char last_char = 0;

const char scancode_to_char[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
    'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
    'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(KEYBOARD_DATA_PORT);
    
    if (scancode > MAX_SCANCODE) return;

    if (scancode == BACKSPACE) {
        int cur_len = string_length(key_buffer);

        if (cur_len > 0) {
            key_buffer[cur_len - 1] = '\0';
            int offset = get_cursor() - 2;
            print_char(' ', offset);
            set_cursor(offset);
        }
    } else if (scancode == ENTER) {
        int cur_len = string_length(key_buffer);
        if (cur_len == 0) {
            print_string("\n>");
        } else {
            parse_command(key_buffer);
        }
        key_buffer[0] = '\0';
    } else {
        int cur_len = string_length(key_buffer);
        char typed_char = scancode_to_char[(int)scancode];
        append(typed_char, key_buffer);
        cur_len += 1;
        char str[2] = {typed_char, '\0'};
        print_string(str);
        last_char = typed_char; // Store the last character pressed
    }
}

void init_keyboard() {
    install_interrupt_handler(33, keyboard_callback); // register keyboard callback as handler for irq1
}

char get_char() {
    char c = last_char;
    last_char = 0; // Reset after reading
    return c;
}
