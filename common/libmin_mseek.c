#include "libmin.h"
#include "libtarg.h"

int libmin_mseek(struct _MFILE *mfile, long offset, int whence)
{
  if (mfile == NULL)
  {
    return -1; // Error: Invalid MFILE pointer
  }

  int new_position = 0;

  switch (whence)
  {
  case SEEK_SET:
    new_position = offset;
    break;
  case SEEK_CUR:
    new_position = mfile->rdptr + offset;
    break;
  case SEEK_END:
    new_position = mfile->data_sz + offset;
    break;
  default:
    return -1; // Error: Invalid `whence` value
  }

  if (new_position < 0 || new_position > mfile->data_sz)
  {
    return -1; // Error: Trying to seek outside the file boundaries
  }

  mfile->rdptr = new_position;
  return 0; // Success
}
