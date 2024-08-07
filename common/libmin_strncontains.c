#include "libmin.h"
#include "libtarg.h"

bool libmin_strncontains(const char *str, char c, size_t n)
{
  for (size_t i = 0; i < n; i++)
  {
    if (str[i] == c)
    {
      return true;
    }
    if (str[i] == '\0')
    {
      return false;
    }
  }
  return false;
}
