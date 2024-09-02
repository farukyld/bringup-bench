#include "libmin.h"
#include "libtarg.h"

char global_buf[2048];

// #define TEST_INPUT
#define TEST_MEMSET
// #define TEST_APPEND_OUTPUT
// #define TEST_OUTPUT
int main()
{
#ifdef TEST_APPEND_OUTPUT
  SFILE *log_file = libmin_sfopen("log.txt", "w");
  libmin_sfprintf(log_file, "outfile1.txt art arda append ile aciliyor\n");
  libmin_sfflush(NULL);
  SFILE *file1 = libmin_sfopen("outfile1.txt", "a");
  SFILE *file2 = libmin_sfopen("outfile1.txt", "a");
  libmin_sfprintf(log_file, "outfile1.txt'ye farkli file pointerlar ile yaziliyor\n");
  libmin_sfflush(NULL);

  libmin_sfprintf(file1, "pointer file1 ile yazilan\n");
  libmin_sfprintf(file2, "pointer file2 ile yazilan\n");
  libmin_sfflush(NULL);

  libmin_sfprintf(log_file, "outfile2.txt once w sonra a mod ile aciliyor\n");
  libmin_sfflush(NULL);

  SFILE *file3 = libmin_sfopen("outfile2.txt", "w");
  SFILE *file4 = libmin_sfopen("outfile2.txt", "a");
  libmin_sfprintf(log_file, "outfile2.txt'ye farkli file pointerlar ile yaziliyor\n");
  libmin_sfflush(NULL);

  libmin_sfprintf(file3, "pointer file3 ile yazilan\n");
  libmin_sfprintf(file4, "pointer file4 ile yazilan\n");
  libmin_sfflush(NULL);

  libmin_sfprintf(log_file, "outfile4.txt iki kere w mod ile aciliyor\n");
  libmin_sfflush(NULL);
  SFILE *file5 = libmin_sfopen("outfile4.txt", "w");
  SFILE *file6 = libmin_sfopen("outfile4.txt", "w");

  libmin_sfprintf(log_file, "outfile5.txt once a sonra w mod ile aciliyor\n");
  libmin_sfflush(NULL);
  SFILE *file7 = libmin_sfopen("outfile5.txt", "a");
  SFILE *file8 = libmin_sfopen("outfile5.txt", "w");

#endif
#ifdef TEST_OUTPUT
  SFILE *file1 = libmin_sfopen("outfile1.txt", "w");
  SFILE *file2 = libmin_sfopen("outfile2.txt", "w");
  libmin_sfprintf(file1, "first to file 1\n");
  libmin_sfprintf(file2, "then to file 2\n");
  libmin_sfprintf(stdout, "to out\n");
  libmin_sfprintf(stderr, "to err\n");

#endif

#ifdef TEST_INPUT
  MFILE *mfile;
  libmin_printf("printing health_check.out\n");
  mfile = libmin_mopen("health_check.out", "r");
  while (!libmin_meof(mfile))
  {
    char buf[1024];
    libmin_mread_bytes(buf, 1024, mfile);
    libmin_printf("%s", buf);
  }
  libmin_mclose(mfile);

  libmin_printf("printing health_check_input.txt\n");
  mfile = libmin_mopen("health_check_input.txt", "r");
  while (!libmin_meof(mfile))
  {
    char buf[1024];
    libmin_mread_bytes(buf, 1024, mfile);
    libmin_printf("%s", buf);
  }
  libmin_mclose(mfile);
#endif

#ifdef TEST_MEMSET
  char *heap_buf = libmin_malloc(2048);
  for (size_t k = 0; k < 20; k++)
  {
    char *offset_buf = heap_buf + k;
    for (size_t i = 0; i < 1024; i++)
    {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++)
      {
        if (offset_buf[j] != 0)
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++)
      {
        if (offset_buf[j] != 'a')
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }
  // do the same test with a stack object
  char stack_buf[2048];
  for (size_t k = 0; k < 20; k++)
  {
    char *offset_buf = stack_buf + k;
    for (size_t i = 0; i < 1024; i++)
    {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++)
      {
        if (offset_buf[j] != 0)
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++)
      {
        if (offset_buf[j] != 'a')
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }

  for (size_t k = 0; k < 20; k++)
  {
    char *offset_buf = global_buf + k;
    for (size_t i = 0; i < 1024; i++)
    {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++)
      {
        if (offset_buf[j] != 0)
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++)
      {
        if (offset_buf[j] != 'a')
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }

  static char static_buf[2048];
  for (size_t k = 0; k < 20; k++)
  {
    char *offset_buf = static_buf + k;
    for (size_t i = 0; i < 1024; i++)
    {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++)
      {
        if (offset_buf[j] != 0)
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++)
      {
        if (offset_buf[j] != 'a')
        {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }

  libmin_printf("memset passed\n");
#endif
  return 0;
}
