#include "libmin.h"

int libmin_getchar(){
  libmin_printf("libmin_getchar is not implemented\n");
  libmin_exit(1);
  return 0;
}

strong_alias(libmin_getchar, getchar);
