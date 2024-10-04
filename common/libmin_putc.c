#include "libmin.h"
#include "libtarg.h"

void
libmin_putc(char c)
{
  libtarg_putc(c);
}

strong_alias(libmin_putc, putc)
