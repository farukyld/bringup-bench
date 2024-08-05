#include "libmin.h"
#include "libtarg.h"

void libmin_exit(int status)
{
  libtarg_fail(status);
}
