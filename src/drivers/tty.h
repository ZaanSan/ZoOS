#ifndef FRAMEBUFFER_H
# define FRAMEBUFFER_H

# include "io.h"

/* Color table */
# define FB_BLACK             0x0
# define FB_BLUE              0x1
# define FB_GREEN             0x2
# define FB_CYAN              0x3
# define FB_RED               0x4
# define FB_MAGENTA           0x5
# define FB_BROWN             0x6
# define FB_L_GREY            0x7
# define FB_D_GREY            0x8
# define FB_L_BLUE            0x9
# define FB_L_GREEN           0xa
# define FB_L_CYAN            0xb
# define FB_L_RED             0xc
# define FB_L_MAGENTA         0xd
# define FB_L_BROWN           0xe
# define FB_WHITE             0xf

/* Framebuffer */
# define FRAMEBUFFER          0x000B8000
# define FB_ROWS              25
# define FB_COLUMNS           80

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/** write:
 * Write the content of a buffer to the screen
 *
 * @param buf The buffer
 */
void fb_write(const char *buf);

/** putc:
 * Write q character to the screen
 *
 * @param c The character
 */
void fb_putc(char c);

/** initialize_tty:
 * Initialize the terminal
 */
void initialize_tty();

/** fb_set_color:
 * Set output color
 *
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_set_color(unsigned char fg, unsigned char bg);

#endif // !FRAMEBUFFER_H
