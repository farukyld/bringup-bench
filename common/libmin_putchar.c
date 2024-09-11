#include "libmin.h"

void libmin_putchar(int c)
{
  libmin_putc(c);
}

strong_alias(libmin_putchar, putchar);
