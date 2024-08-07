#include "libmin.h"
#include "libtarg.h"

bool libmin_strfits(const char *str, size_t n)
{
  return libmin_strncontains(str, '\0', n);
}
