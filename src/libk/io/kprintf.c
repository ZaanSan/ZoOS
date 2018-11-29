
#include <stdarg.h>
#include "kio.h"
#include "tty.h"

/**********************************************************
 * Private lib Kernel IO                                  *
 **********************************************************/

void put_nb(int nb)
{
  int begin;
  int end;

  if (nb < 0)
  {
    fb_putc('-');
    nb = -nb;
  }
  end = nb % 10;
  begin = nb / 10;
  if (begin != 0)
    put_nb(begin);
  fb_putc(end + '0');
}


/**********************************************************
 * Public lib Kernel IO API                               *
 **********************************************************/

void kprintf(const char *format, ...)
{
  va_list ap;
  va_start(ap, format);

  while (*format)
  {
    if (*format != '%')
      fb_putc(*format);
    else
    {
      format++;
      if (!(*format))
        return;
      else if (*format == 'c')
      {
        char c = (char) va_arg(ap, int);
        fb_putc(c);
      }
      else if (*format == 's')
      {
        const char *str = va_arg(ap, const char *);
        fb_write(str);
      }
      else if (*format == 'd')
      {
        int nb = va_arg(ap, int);
        put_nb(nb);
      }
    }
    format++;
  }

  va_end(ap);
}
