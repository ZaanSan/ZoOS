#include "interrupt.h"
#include "idt.h"
#include "io/kio.h"

static interrupt_handler_t interrupt_handlers[IDT_NUM_ENTRIES];

unsigned int register_interrupt_handler(unsigned int interrupt,
                                    interrupt_handler_t handler)
{
    if (interrupt > 255) {
        return 1;
    }
    if (interrupt_handlers[interrupt] != NULL) {
        return 1;
    }

    interrupt_handlers[interrupt] = handler;
    return 0;
}

void interrupt_handler(cpu_state_t state, idt_info_t info, stack_state_t exec)
{
    if (info.idt_index < IDT_NUM_ENTRIES && interrupt_handlers[info.idt_index] != NULL) {
        interrupt_handlers[info.idt_index](state, info, exec);
    } else {
        kprintf("Interrupt handler : unhandled interrupt : %d\n", info.idt_index);
    }
}
