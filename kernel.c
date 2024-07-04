#include "screen_driver.h"
#include <stdint.h>
#include <stddef.h>

// Function to print max-OS text at the top of the screen
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

// Delay function
void delay(uint32_t count) {
    for (volatile uint32_t i = 0; i < count; i++) {
        __asm__ __volatile__("nop");
    }
}

// Simple startup screen function
void startup_screen() {
    clrscr();
    print_string("Starting up...");
    delay(100000000); // Adjust the delay as neededz
}

// Kernel main function
void main() {
    clrscr(); // Clear the screen
    startup_screen(); // Show startup screen
    clrscr(); // Clear the screen again
    print_max_os(); // Print the max-OS text at the top

    // Add your kernel logic here
    while (1) {
        // Halt the CPU
    }
}