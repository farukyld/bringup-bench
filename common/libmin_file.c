// MFILE ve SFILE struct'lari ve API'leri icin cevreleyici yapi.
#include "libmin_file.h"
#include "libmin.h"
#include "libtarg.h"

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

// MFILE SFILE ortak arayuzleri

FILE *libmin_fopen(const char *fname, const char *mode_str)
{
  FILE *file = (FILE *)malloc(sizeof(FILE));
  if (unlikely(file == NULL))
    return NULL;
  if (libmin_strncmp(mode_str, "r", 2) == 0 || libmin_strncmp(mode_str, "rb", 3) == 0)
  {
    file->type = FILE_TYPE_MFILE;
    file->file = libmin_mopen(fname, "r");
  }
  else
  {
    file->type = FILE_TYPE_SFILE;
    file->file = libmin_sfopen(fname, mode_str);
  }
  if (file->file == NULL)
  {
    free(file);
    return NULL;
  }
  return file;
}

strong_alias(libmin_fopen, fopen);

int libmin_fclose(FILE *file)
{
  if (unlikely(file == NULL))
    return -1;
  if (file->type == FILE_TYPE_MFILE)
  {
    libmin_mclose((MFILE *)file->file);
    return 0;
  }
  else
  {
    return libmin_sfclose((SFILE *)file->file);
  }
}

strong_alias(libmin_fclose, fclose);

int libmin_feof(FILE *file)
{
  if (unlikely(file == NULL))
    return -1;
  if (file->type == FILE_TYPE_MFILE)
  {
    return libmin_meof((MFILE *)file->file);
  }
  else
  {
    return false;
  }
}

strong_alias(libmin_feof, feof);

// MFILE icin ozel arayuzler
int libmin_fseek(FILE *file, long offset, int whence)
{
  if (unlikely(file == NULL))
    return -1;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mseek((MFILE *)file->file, offset, whence);
  }
  else
  {
    libmin_printf("libmin_fseek only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_fseek, fseek);

long libmin_ftell(FILE *file)
{
  if (unlikely(file == NULL))
    return -1;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mtell((MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_ftell only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_ftell, ftell);

size_t libmin_fread_bytes(void *ptr, size_t size, FILE *file)
{
  if (unlikely(file == NULL))
    return 0;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mread_bytes(ptr, size, (MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_fread_bytes only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_fread_bytes, fread_bytes);

size_t libmin_fread(void *ptr, size_t size, size_t nmemb, FILE *file)
{
  if (unlikely(file == NULL))
    return 0;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mread(ptr, size, nmemb, (MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_fread only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_fread, fread);

char *libmin_fgets(char *s, size_t size, FILE *file)
{
  if (unlikely(file == NULL))
    return NULL;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mgets(s, size, (MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_fgets only supports MFILE\n");
    libmin_exit(1);
    return NULL;
  }
}

strong_alias(libmin_fgets, fgets);

int libmin_fgetc(FILE *file)
{
  if (unlikely(file == NULL))
    return EOF;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mgetc((MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_fgetc only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_fgetc, fgetc);
strong_alias(libmin_fgetc, getc);

int libmin_ungetc(int c, FILE *file)
{
  if (unlikely(file == NULL))
    return EOF;
  if (likely(file->type == FILE_TYPE_MFILE))
  {
    return libmin_mungetc(c, (MFILE *)file->file);
  }
  else
  {
    libmin_printf("libmin_fungetc only supports MFILE\n");
    libmin_exit(1);
    return EOF;
  }
}

strong_alias(libmin_ungetc, ungetc);

// SFILE icin ozel arayuzler
int libmin_fputc(int c, FILE *file)
{
  if (unlikely(file == NULL))
    return -1;
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_fputc only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  return libmin_sfputc(c, (SFILE *)file->file);
}

strong_alias(libmin_fputc, fputc);

// int libmin_sfputs(const char *str, SFILE *file);
int libmin_fputs(const char *str, FILE *file)
{
  if (unlikely(file == NULL))
    return -1;
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_fputs only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  return libmin_sfputs(str, (SFILE *)file->file);
}

strong_alias(libmin_fputs, fputs);

size_t libmin_fwrite(const void *ptr, size_t ssize, size_t nmemb, FILE *file)
{
  if (unlikely(file == NULL))
    return 0;
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_fwrite only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  return libmin_sfwrite(ptr, ssize, nmemb, file->file);
}

strong_alias(libmin_fwrite, fwrite);

// int libmin_sfprintf(SFILE *file, const char *fmt, ...);
int libmin_fprintf(FILE *file, const char *fmt, ...)
{
  if (unlikely(file == NULL))
    return -1;
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_fprintf only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  va_list ap;
  va_start(ap, fmt);
  int ret = libmin_vsfprintf((SFILE *)file->file, fmt, ap);
  va_end(ap);
  return ret;
}

strong_alias(libmin_fprintf, fprintf);

// int libmin_vsfprintf(SFILE *file, const char *fmt, va_list ap);
int libmin_vfprintf(FILE *file, const char *fmt, va_list ap)
{
  if (unlikely(file == NULL))
    return -1;
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_vfprintf only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  return libmin_vsfprintf((SFILE *)file->file, fmt, ap);
}

strong_alias(libmin_vfprintf, vfprintf);

// int libmin_sfflush(SFILE *file); // aslinda ortak olabilir. ama simdilik sadece sfile icin tanimlanacak.
int libmin_fflush(FILE *file)
{
  if (unlikely(file == NULL))
    return libmin_sfflush(NULL);
  if (unlikely(file->type == FILE_TYPE_MFILE))
  {
    libmin_printf("libmin_fflush only supports SFILE\n");
    libmin_exit(1);
    return EOF;
  }
  return libmin_sfflush((SFILE *)file->file);
}

strong_alias(libmin_fflush, fflush);
