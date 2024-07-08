#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/isr.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/shell.h"
#include "tetris.h"
#include "/Users/manaskumar/Desktop/MAX-OS-P1/essentials/time.h"


struct tetris game;

void timer_callback(registers_t *regs) {
    static int count = 0;
    char cmd;

    count++;
    if (count % 50 == 0) {
        tetris_print(&game);
    }
    if (count % 350 == 0) {
        tetris_gravity(&game);
    }
    if ((cmd = get_char())) {
        tetris_handle_input(&game, cmd);
    }
}

void main() {
    clrscr();
    print_string("Installing interrupt service routines (ISRs).\n");
    interrupt_install();

    print_string("Enabling external interrupts.\n");
    __asm__ __volatile__ ("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print_string("Initializing timer.\n");
    init_timer(100); // Set timer frequency to 100 Hz

    print_string("Starting Tetris Game.\n");
    tetris_init(&game, 20, 10);

    tetris_run(&game, 20, 10);

}