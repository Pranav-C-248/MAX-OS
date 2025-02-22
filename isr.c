#include "isr.h"
#include "idt.h"
#include "port.h"
#include "screen_driver.h"

// char*exception_messages[32] = {
//         "Division By Zero",
//         "Debug",
//         "Non Maskable Interrupt",
//         "Breakpoint",
//         "Into Detected Overflow",
//         "Out of Bounds",
//         "Invalid Opcode",
//         "No Coprocessor",
//         "Double Fault",
//         "Coprocessor Segment Overrun",
//         "Bad TSS",
//         "Segment Not Present",
//         "Stack Fault",
//         "General Protection Fault",
//         "Page Fault",
//         "Unknown Interrupt",
//         "Coprocessor Fault",
//         "Alignment Check",
//         "Machine Check",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved"
// };

//generic handler to print nth reserved interrupt
void isr_handler(registers_t *r) {
    // print_string(exception_messages[r->int_no]);
    // char s[100]="asdasd";
    // print_string(s);
    print_string("ISR ERROR IN ISR.C");
}

//setting each gate.
void interrupt_install(){
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    
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
    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);
    set_idt_gate(34, (uint32_t)irq2);
    set_idt_gate(35, (uint32_t)irq3);
    set_idt_gate(36, (uint32_t)irq4);
    set_idt_gate(37, (uint32_t)irq5);
    set_idt_gate(38, (uint32_t)irq6);
    set_idt_gate(39, (uint32_t)irq7);
    set_idt_gate(40, (uint32_t)irq8);
    set_idt_gate(41, (uint32_t)irq9);
    set_idt_gate(42, (uint32_t)irq10);
    set_idt_gate(43, (uint32_t)irq11);
    set_idt_gate(44, (uint32_t)irq12);
    set_idt_gate(45, (uint32_t)irq13);
    set_idt_gate(46, (uint32_t)irq14);
    set_idt_gate(47, (uint32_t)irq15);


    load_idt();
}


isr interrupt_handlers[256];
void irq_handler(registers_t *r){
    if(interrupt_handlers[r->int_no]!=0){          //check if a function exists to handle the iqr
        isr handler= interrupt_handlers[r->int_no];
        handler(r);
    }
    port_byte_out(0x20, 0x20); // primary EOI
    if (r->int_no >= 40)        
        port_byte_out(0xA0, 0x20); // secondary EOI for ports 8 to 15
}


//n:irq_no ; handler function: pointer to handler function 
void install_interrupt_handler(uint8_t n,isr handler_function){
    interrupt_handlers[n]=handler_function;
} 








