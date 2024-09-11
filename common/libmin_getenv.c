#include "libmin.h"

char* libmin_getenv(const char* name) {
  libmin_printf("libmin_getenv is not implemented\n");
  libtarg_fail(1);
  return NULL;
}

// strong_alias(libmin_getenv, getenv);
