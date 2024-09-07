#ifndef LIBMIN_FILE_H
#define LIBMIN_FILE_H


typedef enum file_type_e{
  FILE_TYPE_MFILE,
  FILE_TYPE_SFILE
} file_type_e;

typedef struct file_t
{
  void *file;
  file_type_e type;
} FILE;

#endif // LIBMIN_FILE_H
