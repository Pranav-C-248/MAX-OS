#pragma once
#include <stdint.h>

extern void init_timer(uint32_t freq);
extern void delay(uint32_t seconds) ;
extern uint32_t get_system_tick();