#pragma once
#include <stdint.h>

typedef struct 
{
    uint32_t ds;    // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // General registers
    uint32_t int_no, err_code; // Interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss; // Automatically pushed by the CPU

}registers_t;

typedef void (*isr)(registers_t*);

extern char *exception_messages[32];

extern isr interrupt_handlers[256];



//declare the isrs , these will be defined in assembly.
// when isr0 is triggered it goes to isr0 label in the assembly and then calls the isr_handle function 
// from within c, whihc just prints the error instead of actually handling it.
// For irq related to keyboard however we need to write a specific and real handler function.

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();

//Declare irqs 0 to 15

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void isr_handler(registers_t* r);
void interrupt_install(); // calls set_idt_gate and maps each nth irq to nth handler
void install_interrupt_handler(uint8_t n,isr handler_function); //n:irq_no ; handler function: pointer to handler function 


//keyboard_handler functions 
//IRQ1 calls this dude to solve irq1
static void keyboard_callback(registers_t *regs);
void identify_key(uint8_t scancode);

