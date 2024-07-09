#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/isr.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/shell.h"
#include "tetris.h"
//#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/time.h"

void print_max_os() {
    const char *max_os_text = "max-OS";
    int length = 6; // Length of "max-OS"
    int row = 0; // Top row
    int col = (MAX_COLS - length) / 2;
    int offset = get_offset(row, col);
    for (int i = 0; i < length; i++) {
        set_char(max_os_text[i], offset + 2 * i);
    }
}



void startup_screen() {
    clrscr();
    print_string("Starting up...");
}
void main() {
    clrscr();
    startup_screen();
    print_max_os();
    
    print_string("Installing interrupt service routines (ISRs).\n");
    interrupt_install();

    print_string("Enabling external interrupts.\n");
    __asm__ __volatile__ ("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();


    print_string("Initialized Shell\n");
    initate_shell();
    print_string(">");
}
