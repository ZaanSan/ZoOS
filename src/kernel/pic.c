#include "pic.h"
#include "io.h"

void initialize_pic(void)
{
  /* ICW1 */
  outb(PIC1_PORT_A, PIC1_ICW1);
  outb(PIC2_PORT_A, PIC2_ICW1);

  /* ICW2 */
  outb(PIC1_PORT_B, PIC1_ICW2);
  outb(PIC2_PORT_B, PIC2_ICW2);

  /* ICW3 */
  outb(PIC1_PORT_B, PIC1_ICW3);
  outb(PIC2_PORT_B, PIC2_ICW3);

  /* ICW4 */
  outb(PIC1_PORT_B, PIC1_ICW4);
  outb(PIC2_PORT_B, PIC2_ICW4);

  pic_mask(0xEC, 0xFF);
}

void pic_acknowledge()
{
  outb(PIC1_PORT_A, PIC_EOI);
  outb(PIC2_PORT_A, PIC_EOI);
}

void pic_mask(unsigned char mask1, unsigned char mask2)
{
  outb(PIC1_PORT_B, mask1);
  outb(PIC2_PORT_B, mask2);
}
