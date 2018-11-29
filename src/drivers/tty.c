#include "tty.h"

/**********************************************************
* Private kernel variables declaration                    *
**********************************************************/

static unsigned char fg_color;
static unsigned char bg_color;

/**********************************************************
* Private kernel functions declaration                    *
**********************************************************/

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer. Defined in framebuffer.c
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 */
void fb_write_cell(unsigned int i, char c);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_get_cursor_position:
 *  Get the cursos position
 *
 *  @return The current cursor offset
 */
unsigned int fb_get_cursor_offset();

/** fb_get_row:
 *  Get the framebuffer row for a given offset
 *fb_get_cursor_position
 * @param offset The given offset
 * @return The framebuffer row
 */
unsigned int fb_get_row(unsigned int offset);

/** fb_get_col:
 *  Get the framebuffer column for a given offset
 *
 * @param offset The given offset
 * @return The framebuffer column
 */
unsigned int fb_get_col(unsigned int offset);

/** fb_get_offset:
 *  Get the framebuffer offset for given row and col
 *
 * @param row The given row
 * @param col The given column
 * @return The current cursor offset
 */
unsigned int fb_get_offset(int row, int col);

/** scrollup:
 *  Scroll the text up
 *
 *  @param Number of line to scroll
 */
void scrollup(unsigned int n);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

 void fb_write(const char *buf)
 {
   unsigned int i = 0;

   while (buf[i])
   {
     fb_putc(buf[i]);
     i++;
   }
 }

 void fb_putc(char c)
 {
   unsigned int offset = fb_get_cursor_offset();
   unsigned int row = fb_get_row(offset);
   unsigned int col = fb_get_col(offset);

   if (c == '\n')
   {
     row++;
     col = 0;
   }
   else
   {
     fb_write_cell(offset, c);
     col++;
     if (col >= FB_COLUMNS)
     {
       col = 0;
       row++;
     }
   }
   if (row >= FB_ROWS)
    {
      scrollup(1);
      row--;
    }
    fb_move_cursor(fb_get_offset(row, col));
 }

 void initialize_tty()
 {
   fg_color = FB_BLACK;
   bg_color = FB_L_GREY;
   unsigned int i = 0;
   while (i < FB_ROWS * FB_COLUMNS)
   {
     fb_write_cell(i, ' ');
     i++;
   }
   fb_move_cursor(0);
 }

 void fb_set_color(unsigned char fg, unsigned char bg)
 {
   fg_color = fg;
   bg_color = bg;
 }

 /**********************************************************
 * Private kernel functions                               *
 **********************************************************/

void fb_write_cell(unsigned int i, char c)
{
    char *fb = (char *)FRAMEBUFFER;
    i *= 2;
    fb[i] = c;
    fb[i + 1] = ((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
}

void fb_move_cursor(unsigned short pos)
{
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

unsigned int fb_get_cursor_offset()
{
  int offset;

  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  offset = inb(FB_DATA_PORT) << 8;
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  offset |= inb(FB_DATA_PORT);
  return (offset);
}

unsigned int fb_get_row(unsigned int offset)
{
  return (offset / FB_COLUMNS);
}

unsigned int fb_get_col(unsigned int offset)
{
  return (offset % FB_COLUMNS);
}

unsigned int fb_get_offset(int row, int col)
{
  return (row * FB_COLUMNS + col);
}

void scrollup(unsigned int n)
{
  char *fb;
  char *tmp;

  for (fb = (char*)FRAMEBUFFER;
       fb < (char *)(FRAMEBUFFER + FB_ROWS * FB_COLUMNS * 2);
       fb += 2)
  {
    tmp = (char*)(fb + n * 160);

    if (tmp < (char *)(FRAMEBUFFER + FB_ROWS * FB_COLUMNS * 2))
    {
      *fb = *tmp;
      *(fb + 1) = *(tmp + 1);
    }
    else
    {
      *fb = 0;
      *(fb + 1) = ((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
    }
  }
}
