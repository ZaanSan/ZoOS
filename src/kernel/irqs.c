#include "irqs.h"
#include "idt.h"
#include "interrupt.h"
#include "commons.h"
#include "pic.h"

void irq_32(struct cpu_state state,
            struct idt_info info,
            struct stack_state exec)
{
  UNUSED_ARG(state);
  UNUSED_ARG(info);
  UNUSED_ARG(exec);
  pic_acknowledge();
}

void initialize_irq()
{
  register_interrupt_handler(32, (interrupt_handler_t)&irq_32);
}
