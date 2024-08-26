#include "libmin.h"
#include "libtarg.h"

char global_buf[2048];

// #define TEST_INPUT
#define TEST_MEMSET

int main()
{

#ifdef TEST_INPUT
  MFILE *mfile;
  libmin_printf("printing health_check.out\n");
  mfile = libmin_mopen("health_check.out", "r");
  while (!libmin_meof(mfile)) {
    char buf[1024];
    libmin_mread(buf, 1024, mfile);
    libmin_printf("%s", buf);
  }
  libmin_mclose(mfile);

  libmin_printf("printing health_check_input.txt\n");
  mfile = libmin_mopen("health_check_input.txt", "r");
  while (!libmin_meof(mfile))
  {
    char buf[1024];
    libmin_mread(buf, 1024, mfile);
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
