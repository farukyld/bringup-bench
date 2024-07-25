#include "libmin.h"

int
main(void)
{
  libmin_printf("This is a test!, %d, %f...\n", 23, 44.4);


#ifndef TARGET_SPIKE
  libmin_success();
#else
return 0;
#endif
  return 0;
}


