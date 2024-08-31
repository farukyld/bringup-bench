#include "libmin.h"
#include "libtarg.h"

MFILE *stdin;

void init_stdin()
{
  stdin = libmin_malloc(sizeof(MFILE));
  stdin->fname = "";
  stdin->data = "";
  stdin->data_sz = 1;
  stdin->rdptr = 0;
}
