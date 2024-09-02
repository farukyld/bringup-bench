#include "libmin.h"
#include "libtarg.h"

long libmin_mtell(MFILE *mfile)
{
  if (mfile == NULL)
  {
    return -1; // Error: Invalid MFILE pointer
  }

  return mfile->rdptr;
}
