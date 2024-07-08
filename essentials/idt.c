/*the general flow of interrupts is as follows :
1) Hardware sends an Interrupt request(IRQ) ,with a particular number, to Programmable Interrupt Controller.

2) PIC then sends this to the CPU depending on priority

3) CPU then looks up at the Interrupt Descriptor Table to see , which "function"/handler to call for this 
    particular interrupt.

4) ISRs are basically the handlers for the first 32 basic errors reserved in the cpu.

5) Each isr number refers to a particular error , ex: isr0 to divide by zero.

6) CPU executes the handler code, and then send end of interrupt EOI, and resumes normal execution

Work Flow:

1) IDT has 256 entries , each called a gate.
    -each gate has various blah blah. Mainly it has the memory location of the interrupt handlers
    for every irq and isr.
    -this memory location is of 32 bit , so it is stored in 2 16 bit parts , high and low.
    - how we're ggonna code this is like , make a struct of type idt_gate, and create an array of 256 
    idt gates, called idt :). then create a function , that takes in IRQ number and IRQ handler address
    and stores it as, idt[IRQ_N].offset=IRQ_HANDLER, with various  blah blah

2) Now we gotta set up ISRs , which basically are handlers. Well be doing generric which takes in the 
    isr and prints the error msg. isr_handler(register* r)
   -We need to write assembly which calls a handler and passes a particular isr which was invoked

3) Then we remap the PIC , which idk whats happening there. 

4) Then we set up the irq in same way as isr, write a handler function and define in assembly.
    Note: There are only 16 irqs, 0-15

5) Then we write handlers for keyboard interrupts and then done :). 

*/

#include "idt.h"
#include <stdint.h>

idt_gate_t idt[256];
idt_descriptor_t idt_descriptor;

void set_idt_gate(int n,uint32_t handler){
    idt[n].low_offset=low_16(handler);
    idt[n].selector=0x08;
    idt[n].always0=0;
    idt[n].flags=0x8e;
    idt[n].high_offset=high_16(handler);
}

void load_idt(){
    idt_descriptor.limit=256*sizeof(idt_gate_t)-1;
    idt_descriptor.base_address=(uint32_t)&idt;
    asm volatile("lidt (%0)" : : "r" (&idt_descriptor));
}