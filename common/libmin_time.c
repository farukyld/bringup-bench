#include "libmin.h"
#include  "libtarg.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

time_t libmin_time(time_t *timer)
{
  time_t cycles = libtarg_get_cycles();
  if (timer != NULL)
    *timer = cycles;
  return cycles;
}
