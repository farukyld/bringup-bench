#include "libmin_file.h"
#include "libmin.h"
#include "libtarg.h"

FILE *stdin;

void init_stdin()
{
  stdin = libmin_malloc(sizeof(FILE));
  stdin->type = FILE_TYPE_MFILE;
  stdin->file = libmin_malloc(sizeof(MFILE));
  MFILE *mfile = (MFILE *)stdin->file;
  mfile->fname = "";
  mfile->data = (uint8_t*)"";
  mfile->data_sz = 1;
  mfile->rdptr = 0;
}
