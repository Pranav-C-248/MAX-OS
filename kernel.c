#include "screen_driver.h"
#include "keyboard.h"
#include "isr.h"
#include "util.h"
#include "shell.h"
#include "tetris.h"
// #include "time.h"
#include "memory.h"



void main() {
    clrscr();
    print_string("Installing interrupt service routines (ISRs).\n");
    interrupt_install();

    // print_string("Enabling external interrupts.\n");
    __asm__ __volatile__ ("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
    // print_string("Initialized Shell\n");

    // initate_shell();
    // print_string(">");

    print_string("Initializing Dynamic memory.\n");
    init_dynamic_memory();
    int *a=mallok(20*sizeof(int));
    for(int i=0;i<20;i++){
        *(a+i)=10;
    }
    for(int i=0;i<20;i++){
        print_int(*(a+i));
    }

    

}