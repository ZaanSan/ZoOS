#ifndef INTERRUPT_H
# define INTERRUPT_H

#include <stddef.h>

struct idt_info {
	unsigned int idt_index;
	unsigned int error_code;
} __attribute__((packed));
typedef struct idt_info idt_info_t;

struct cpu_state {
  unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int edx;
	unsigned int ecx;
	unsigned int ebx;
	unsigned int eax;
  unsigned int esp;
} __attribute__((packed));
typedef struct cpu_state cpu_state_t;

struct stack_state {
  unsigned int eip;
  unsigned int cs;
	unsigned int eflags;
	unsigned int user_esp; /* not always safe to derefence! */
	unsigned int user_ss; /* not always safe to derefence! */
} __attribute__((packed));
typedef struct stack_state stack_state_t;

typedef  void (*interrupt_handler_t)(struct cpu_state cpu, struct idt_info info, struct stack_state stack);
unsigned int register_interrupt_handler(unsigned int interrupt, interrupt_handler_t handler);
void enable_interrupts(void);
void disable_interrupts(void);

#endif // !INTERRUPT_H
