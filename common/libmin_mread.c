#include "libmin.h"
#include "libtarg.h"

/* read a buffer from the in-memory file */
size_t
libmin_mread_bytes(void *_ptr, size_t size, MFILE *mfile)
{
  char *ptr = _ptr;
  size_t remaining_bytes = mfile->data_sz - mfile->rdptr;
  size_t bytes_to_read = MIN(size, remaining_bytes);
  memcpy(ptr, mfile->data + mfile->rdptr, bytes_to_read);
  mfile->rdptr += bytes_to_read;
  return bytes_to_read;
}

size_t libmin_mread(void *_ptr, size_t size, size_t nmemb, MFILE *mfile)
{
  size_t remaining_bytes = mfile->data_sz - mfile->rdptr;
  size_t elements_to_read = MIN(size * nmemb, remaining_bytes) / size;
  size_t bytes_to_read = elements_to_read * size;
  memcpy(_ptr, mfile->data + mfile->rdptr, bytes_to_read);
  mfile->rdptr += bytes_to_read;
  return elements_to_read;
}
