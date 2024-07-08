#include "time.h"
#include "screen_driver.h"
#include "port.h"
#include "util.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    // if(tick%72==0){
    // print_string("Tick: ");
    // print_int(tick);
    // print_string("\n");
    // }
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    install_interrupt_handler(32, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180/freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}
void delay(uint32_t seconds) {
    uint32_t target_tick = tick + (seconds*72); // Assuming `freq` is the frequency in Hz
    while (tick < target_tick) ;
}

uint32_t get_system_tick(){
    return tick;
}