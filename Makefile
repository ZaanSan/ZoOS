CRTI_OBJ = src/kernel/crti.o
CRTBEGIN_OBJ = /usr/lib/gcc/x86_64-linux-gnu/8/32/crtbegin.o
CRTEND_OBJ = /usr/lib/gcc/x86_64-linux-gnu/8/32/crtend.o
CRTN_OBJ = src/kernel/crtn.o

OBJECTS = src/kernel/loader.o												\
					src/kernel/gdt_asm.o											\
					src/kernel/gdt.o													\
					src/kernel/idt_asm.o											\
					src/kernel/idt.o													\
					src/kernel/interrupt_asm.o								\
					src/kernel/interrupt.o										\
					src/kernel/pic.o													\
					src/kernel/irqs.o													\
					src/kernel/kmain.o												\
					src/kernel/io.o														\
					src/drivers/tty.o													\
					src/drivers/serial.o											\
					src/drivers/keyboard.o										\
					src/libk/io/kprintf.o											\
					src/libk/string/kstrlen.o									\
					src/libk/string/kmemset.o									\
					src/libk/string/kmemcpy.o									\

ALL_OBJECTS = $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJECTS) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJECTS = $(CRTI_OBJ) $(OBJECTS) $(CRTN_OBJ)

CC = i686-elf-gcc

CFLAGS = -nostdlib -fno-builtin -fno-stack-protector 								\
				 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -lgcc

LINKER = src/kernel/link.ld

LDFLAGS = -T $(LINKER)

INCLUDE = -Isrc/kernel/ -Isrc/drivers/ -Isrc/libk/

all: kernel.elf

kernel.elf: $(ALL_OBJECTS) $(LINKER)
	$(CC) $(LDFLAGS) -o $@ $(CFLAGS) $(ALL_OBJECTS)
	grub-file --is-x86-multiboot kernel.elf

os.iso: kernel.elf
		cp kernel.elf iso/boot/kernel.elf
		genisoimage -R                              \
								-b boot/grub/stage2_eltorito    \
								-no-emul-boot                   \
								-boot-load-size 4               \
								-A os                           \
								-input-charset utf8             \
								-quiet                          \
								-boot-info-table                \
								-o os.iso                       \
								iso

run: os.iso
		bochs -f bochsrc.txt -q

%.o: %.c
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(INCLUDE)

%.o: %.s
			$(CC) -MD -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
		rm -rf $(INTERNAL_OBJECTS) $(INTERNAL_OBJECTS:.o=.d) kernel.elf os.iso com1.out

clean_obj:
		rm -rf $(INTERNAL_OBJECTS) $(INTERNAL_OBJECTS:.o=.d)

re: clean run
