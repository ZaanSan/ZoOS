#include "kstring.h"

/**********************************************************
 * Public lib Kernel string API                           *
 **********************************************************/

void *kmemcpy(void *dest, const void *src, size_t size)
{
  unsigned char *d = (unsigned char *)dest;
  unsigned char *s = (unsigned char *)src;

  for (size_t i = 0; i < size; i++)
    d[i] = s[i];
  return dest;
}
