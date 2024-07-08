#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/screen_driver.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/keyboard.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/isr.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/util.h"
#include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/shell.h"
// #include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/main/tetris.h"
// #include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/time.h"
// #include "/mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/memory.h"
// #include "tetris.h"



void main() {
    clrscr();
    print_string("Installing interrupt service routines (ISRs).\n");
    interrupt_install();

    print_string("Enabling external interrupts.\n");
    __asm__ __volatile__ ("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print_string("Initialized Shell\n");
    initate_shell();
    print_string(">");

    // print_string("Initializing Dynamic memory.\n");
    
//     init_dynamic_memory();
//        print_string("Starting Tetris Game.\n");
//     start_tetris();  
// 
}

// This function needs to be defined in tetris.c
// void start_tetris() {
    
//     tetris_run(10,20);
// }
  
