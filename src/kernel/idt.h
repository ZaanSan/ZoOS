#ifndef IDT_H_
# define IDT_H_

# include "interrupt.h"

#define IDT_NUM_ENTRIES               256

#define IDT_INTERRUPT_GATE_TYPE       0
#define IDT_TRAP_GATE_TYPE		        1

#define IDT_TIMER_INTERRUPT_INDEX     0x20
#define IDT_KEYBOARD_INTERRUPT_INDEX  0x21

#define CREATE_IDT_GATE(idx) \
    idt_create_gate(idx, (unsigned int) &interrupt_handler_##idx,\
                    IDT_TRAP_GATE_TYPE, PL0);

#define DECLARE_INTERRUPT_HANDLER(i) void interrupt_handler_##i(void)



struct idt {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));

struct idt_entry {
  unsigned short offset_low;
  unsigned short seg_sel;
  unsigned char zero;
  unsigned char config;
  unsigned short offset_high;
} __attribute__((packed));

/** load_idt:
*  Load the interrupt descriptor table
*
*  @param gdt The pointer on the idt structure
*/
void load_idt(struct idt *idt);

void initialize_idt(void);

#endif // !IDT_H_
