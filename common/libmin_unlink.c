#include "libmin.h"

int libmin_unlink(const char *pathname)
{
  libmin_printf("unlink is not implemented\n");
  libmin_exit(1);
  return -1;
}

strong_alias(libmin_unlink, unlink);
