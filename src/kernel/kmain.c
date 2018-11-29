#include "kernel.h"

void initialize_kernel()
{
	disable_interrupts();

	set_serial_port(SERIAL_COM1_BASE);
	initialize_serial_logging();
	log(INFO, "Logging system is ready.\n");

	initialize_tty();
	log(INFO, "Tty driver is set up.\n");

	kprintf("Loading GDT\n");
	initialize_gdt();
	log(INFO, "Global descriptor table loaded.\n");

	kprintf("Loading IDT\n");
	initialize_idt();
	log(INFO, "Interrupt descriptor table loaded.\n");

	kprintf("Configure PIC\n");
	initialize_pic();
	log(INFO, "Programmable interrupt controller loaded.\n");

	kprintf("Initialize keyboard driver\n");
	kbd_init();
	log(INFO, "Keyboard interrupt registered.\n");

	initialize_irq();

	kprintf("Enabling hardware interrupt\n");
	enable_interrupts();
	log(INFO, "Hardware interrupts enabled.\n");

	kprintf("\n------ End of initialization -----\n\n");
}

int kmain()
{
	initialize_kernel();

	kprintf("Hello world !\n");
	fb_set_color(FB_BLACK, FB_RED);
	kprintf("This is ZoOS\n");
	fb_set_color(FB_BLACK, FB_L_GREY);

	char buff[10];
	int size = 10;
	int read;
	kmemset(buff, 0, size);
	while (1)
	{
			read = kbd_read(buff, size);
			if (read > 0)
			{
				kprintf("Got keyboard input : %s\n", buff);
				kmemset(buff, 0, size);
			}
	}

	return (0);
}
