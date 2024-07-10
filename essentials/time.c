#include "time.h"
#include "screen_driver.h"
#include "port.h"
#include "util.h"
#include "isr.h"
#include <stdint.h>    // For uint32_t, uint8_t

uint32_t tick = 0;

// Timer callback function
static void timer_callback(registers_t *regs) {
    tick++;
}

// Initialize the timer
void init_timer(uint32_t freq) {
    install_interrupt_handler(72, timer_callback);

    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}

// Delay function
void delay(uint32_t seconds) {
    uint32_t target_tick = tick + (seconds * 100);
    while (tick < target_tick);
}

// Get the current system tick
uint32_t get_system_tick(){
    return tick;
}
