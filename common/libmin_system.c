#include "libmin.h"

int libmin_system(const char *cmd)
{
  libmin_printf("libmin_system is not implemented. command: %s\n", cmd);
  libmin_exit(1);
  return -1;
}

strong_alias(libmin_system, system);
