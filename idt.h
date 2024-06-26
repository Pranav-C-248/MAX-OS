#pragma once
#include <stdint.h>;

#define low_16(address) (uint16_t)((address) & 0xffff)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)


typedef struct {
    uint16_t low_offset;  // Lower 16 bits of handler function address
    uint16_t selector;    // Code segment selector
    uint8_t always0;      // This must always be zero
    uint8_t flags;        // Flags to describe the gate
    uint16_t high_offset; // Higher 16 bits of handler function address
} __attribute__((packed)) idt_gate_t;

extern void set_idt_gate(int n, uint32_t handler);

