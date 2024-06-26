#include "isr.h"
#include "idt.h"
#include "screen_driver.h"

//generic handler to print nth reserved interrupt
void isr_handler(registers_t *r) {
    print_string(exception_messages[r->int_no]);
    print_nl();
}

//setting each gate.
void interrupt_install(){
    set_idt_gate(0,isr0);
    set_idt_gate(0,isr1);
    set_idt_gate(0,isr2);
    set_idt_gate(0,isr3);
    set_idt_gate(0,isr4);
    set_idt_gate(0,isr5);
    set_idt_gate(0,isr6);
    set_idt_gate(0,isr7);
    set_idt_gate(0,isr8);
    set_idt_gate(0,isr9);
    set_idt_gate(0,isr10);
    set_idt_gate(0,isr11);
    set_idt_gate(0,isr12);
    set_idt_gate(0,isr13);
    set_idt_gate(0,isr14);
    set_idt_gate(0,isr15);
    set_idt_gate(0,isr16);
    set_idt_gate(0,isr17);
    set_idt_gate(0,isr18);
    set_idt_gate(0,isr19);
    set_idt_gate(0,isr20);
    set_idt_gate(0,isr21);
    set_idt_gate(0,isr22);
    set_idt_gate(0,isr23);
    set_idt_gate(0,isr24);
    set_idt_gate(0,isr25);
    set_idt_gate(0,isr26);
    set_idt_gate(0,isr27);
    set_idt_gate(0,isr28);
    set_idt_gate(0,isr29);
    set_idt_gate(0,isr30);
    set_idt_gate(0,isr31);
    
    // ICW1
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // ICW2
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // ICW3
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    // ICW4
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // OCW1
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    //set up irqs now
    set_idt_gate(0,irq0);
    set_idt_gate(0,irq1);
    set_idt_gate(0,irq2);
    set_idt_gate(0,irq3);
    set_idt_gate(0,irq4);
    set_idt_gate(0,irq5);
    set_idt_gate(0,irq6);
    set_idt_gate(0,irq7);
    set_idt_gate(0,irq8);
    set_idt_gate(0,irq9);
    set_idt_gate(0,irq10);
    set_idt_gate(0,irq11);
    set_idt_gate(0,irq12);
    set_idt_gate(0,irq13);
    set_idt_gate(0,irq14);
    set_idt_gate(0,irq15);
}

void irq_handler(registers_t *r){

    //check if a function exists to handle the iqr
    if(interrupt_handlers[r->int_no]!=0){
        isr handler= interrupt_handlers[r->int_no];
        handler(r);
    }
    port_byte_out(0x20, 0x20); // primary EOI
    if (r->int_no >= 40)        
        port_byte_out(0xA0, 0x20); // secondary EOI for ports 8 to 15
}


/*To do:
-implement handler for keyboard interrupt
-implement print_int correctly

*/






