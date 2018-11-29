#include "idt.h"
#include "constants.h"

/**********************************************************
* Private kernel variables declaration                    *
**********************************************************/

struct idt_entry 	idte[IDT_NUM_ENTRIES];

/**********************************************************
* Private kernel functions declaration                    *
**********************************************************/

/** idt_create_gate:
 * Initialize an entry in idt.
 */
void idt_create_gate(unsigned char n, unsigned int handler,
                     unsigned char type, unsigned char pl);

DECLARE_INTERRUPT_HANDLER(0);
DECLARE_INTERRUPT_HANDLER(1);
DECLARE_INTERRUPT_HANDLER(2);
DECLARE_INTERRUPT_HANDLER(3);
DECLARE_INTERRUPT_HANDLER(4);
DECLARE_INTERRUPT_HANDLER(5);
DECLARE_INTERRUPT_HANDLER(6);
DECLARE_INTERRUPT_HANDLER(7);
DECLARE_INTERRUPT_HANDLER(8);
DECLARE_INTERRUPT_HANDLER(9);
DECLARE_INTERRUPT_HANDLER(10);
DECLARE_INTERRUPT_HANDLER(11);
DECLARE_INTERRUPT_HANDLER(12);
DECLARE_INTERRUPT_HANDLER(13);
DECLARE_INTERRUPT_HANDLER(14);
DECLARE_INTERRUPT_HANDLER(15);
DECLARE_INTERRUPT_HANDLER(16);
DECLARE_INTERRUPT_HANDLER(17);
DECLARE_INTERRUPT_HANDLER(18);
DECLARE_INTERRUPT_HANDLER(19);

/* IRQs */
DECLARE_INTERRUPT_HANDLER(32);
DECLARE_INTERRUPT_HANDLER(33);
DECLARE_INTERRUPT_HANDLER(34);
DECLARE_INTERRUPT_HANDLER(35);
DECLARE_INTERRUPT_HANDLER(36);
DECLARE_INTERRUPT_HANDLER(37);
DECLARE_INTERRUPT_HANDLER(38);
DECLARE_INTERRUPT_HANDLER(39);
DECLARE_INTERRUPT_HANDLER(40);
DECLARE_INTERRUPT_HANDLER(41);
DECLARE_INTERRUPT_HANDLER(42);
DECLARE_INTERRUPT_HANDLER(43);
DECLARE_INTERRUPT_HANDLER(44);
DECLARE_INTERRUPT_HANDLER(45);
DECLARE_INTERRUPT_HANDLER(46);
DECLARE_INTERRUPT_HANDLER(47);


/**********************************************************
* Private kernel function                                 *
**********************************************************/

void idt_create_gate(unsigned char n, unsigned int handler,
                     unsigned char type, unsigned char pl)
{
    idte[n].offset_low = handler & 0x0000FFFF;
   idte[n].offset_high = (handler >> 16) & 0x0000FFFF;

   idte[n].seg_sel = SEGSEL_KERNEL_CS;
   idte[n].zero = 0;

   /* name | value | size | desc
    * --------------------------
    * P    |     1 |    1 | segment present in memory
    * DPL  |    pl |    2 | privilege level
    * 0    |     0 |    1 | a zero bit
    * D    |     1 |    1 | size of gate, 1 = 32 bits, 0 = 16 bits
    * 1    |     1 |    1 | a one bit
    * 1    |     1 |    1 | a one bit
    * T    |  type |    1 | the type of the gate, 1 = trap, 0 = interrupt
    */
    idte[n].config =
    (0x01 << 7)          |
    ((pl & 0x03)  << 5)  |
    (0x01 << 3)          |
    (0x01 << 2)          |
    (0x01 << 1)          |
    type;
}


/**********************************************************
* Public kernel API function                              *
**********************************************************/

void initialize_idt()
{
  struct idt idt;
  idt.limit = IDT_NUM_ENTRIES * sizeof(struct idt_entry);
  idt.base  = (unsigned int) &idte;

  /* Protected mode exceptions */
  CREATE_IDT_GATE(0);
  CREATE_IDT_GATE(1);
  CREATE_IDT_GATE(2);
  CREATE_IDT_GATE(3);
  CREATE_IDT_GATE(4);
  CREATE_IDT_GATE(5);
  CREATE_IDT_GATE(6);
  CREATE_IDT_GATE(7);
  CREATE_IDT_GATE(8);
  CREATE_IDT_GATE(9);
  CREATE_IDT_GATE(10);
  CREATE_IDT_GATE(11);
  CREATE_IDT_GATE(12);
  CREATE_IDT_GATE(13);
  CREATE_IDT_GATE(14);
  CREATE_IDT_GATE(15);
  CREATE_IDT_GATE(16);
  CREATE_IDT_GATE(17);
  CREATE_IDT_GATE(18);
  CREATE_IDT_GATE(19);

  /* IRQs */
  CREATE_IDT_GATE(32);
  CREATE_IDT_GATE(33);
  CREATE_IDT_GATE(34);
  CREATE_IDT_GATE(35);
  CREATE_IDT_GATE(36);
  CREATE_IDT_GATE(37);
  CREATE_IDT_GATE(38);
  CREATE_IDT_GATE(39);
  CREATE_IDT_GATE(40);
  CREATE_IDT_GATE(41);
  CREATE_IDT_GATE(42);
  CREATE_IDT_GATE(43);
  CREATE_IDT_GATE(44);
  CREATE_IDT_GATE(45);
  CREATE_IDT_GATE(46);
  CREATE_IDT_GATE(47);

  load_idt(&idt);
}
