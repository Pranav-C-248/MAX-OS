#include "screen_driver.h"
#include "keyboard.h"
#include "isr.h"
#include "util.h"
#include "shell.h"


void main() {
    clrscr();
    print_string("Installing interrupt service routines (ISRs).\n");
    interrupt_install();

    // print_string("Enabling external interrupts.\n");
    __asm__ __volatile__ ("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
    print_string("Initialized Shell\n");

    initate_shell();
    print_string(">");
    

}