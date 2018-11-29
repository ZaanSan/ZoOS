#ifndef KSTRING_H
# define KSTRING_H

# include <stddef.h>

/**********************************************************
 * Public lib Kernel string API                           *
 **********************************************************/

size_t   kstrlen(const char *str);
void    *kmemset(void *ptr, int value, size_t size);
void    *kmemcpy(void *dest, const void *src, size_t size);

#endif // !KSTRING_H
