#ifndef KERNEL_H
# define KERNEL_H

# include "constants.h"

# include "gdt.h"
# include "idt.h"
# include "interrupt.h"
# include "pic.h"
# include "irqs.h"

# include "tty.h"
# include "serial.h"
# include "keyboard.h"

# include "commons.h"

# include "io/kio.h"
# include "string/kstring.h"

#endif // !KERNEL_H
