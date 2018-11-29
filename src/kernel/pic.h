#ifndef PIC_H
# define PIC_H

# define PIC1_START      0x20
# define PIC2_START      0x28
# define PIC_NUM_IRQS    16

# define PIT_INT_IDX     PIC1_START
# define KBD_INT_IDX     PIC1_START + 1

# define COM1_INT_IDX    PIC1_START + 4
# define COM2_INT_IDX   PIC1_START + 3

# define PIC1_PORT_A 0x20
# define PIC1_PORT_B 0x21

# define PIC2_PORT_A 0xA0
# define PIC2_PORT_B 0xA1

# define PIC1_ICW1   0x11 /* Initialize the PIC and enable ICW4 */
# define PIC2_ICW1   PIC1_ICW2

# define PIC1_ICW2   0x20 /* IRQ 0-7 will be remapped to IDT index 32 - 39 */
# define PIC2_ICW2   0x28 /* IRQ 8-15 will be remapped to IDT index 40 - 47 */

# define PIC1_ICW3   0x04 /* PIC1 is connected to PIC2 via IRQ2 */
# define PIC2_ICW3   0x02 /* PIC2 is connected to PIC1 via IRQ1 */

# define PIC1_ICW4   0x05 /* 8086/88 mode is enabled and PIC1 is master */
# define PIC2_ICW4   0x01 /* 8086/88 mode is enabled */

# define PIC_EOI 0x20

void initialize_pic(void);

/** pic_acknowledge:
     *  Acknowledges an interrupt from either PIC 1 or PIC 2.
     *
     *  @param num The number of the interrupt
     */
void pic_acknowledge(void);

void pic_mask(unsigned char mask1, unsigned char mask2);

#endif
