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

strong_alias(libmin_time, time);

double libmin_difftime(time_t time1, time_t time0)
{
  return (double)time1 - (double)time0;
}

strong_alias(libmin_difftime, difftime);
