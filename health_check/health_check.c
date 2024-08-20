#include "libmin.h"
#include "libtarg.h"

char global_buf[2048];


int main()
{
  char*heap_buf = libmin_malloc(2048);
  for (size_t k = 0; k < 20; k++) {
    char *offset_buf = heap_buf + k;
    for (size_t i = 0; i < 1024; i++) {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++) {
        if (offset_buf[j] != 0) {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++) {
        if (offset_buf[j] != 'a') {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }
  // do the same test with a stack object
  char stack_buf[2048];
  for (size_t k = 0; k < 20; k++) {
    char *offset_buf = stack_buf + k;
    for (size_t i = 0; i < 1024; i++) {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++) {
        if (offset_buf[j] != 0) {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++) {
        if (offset_buf[j] != 'a') {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }
  
  for (size_t k = 0; k < 20; k++) {
    char *offset_buf = global_buf + k;
    for (size_t i = 0; i < 1024; i++) {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++) {
        if (offset_buf[j] != 0) {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++) {
        if (offset_buf[j] != 'a') {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }

  static char static_buf[2048];
  for (size_t k = 0; k < 20; k++) {
    char *offset_buf = static_buf + k;
    for (size_t i = 0; i < 1024; i++) {
      libmin_memset(offset_buf, 0, 1024);
      for (size_t j = 0; j < 1024; j++) {
        if (offset_buf[j] != 0) {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
      libmin_memset(offset_buf, 'a', i);
      for (size_t j = 0; j < i; j++) {
        if (offset_buf[j] != 'a') {
          libmin_printf("memset failed\n");
          return 1;
        }
      }
    }
  }

  libmin_printf("memset passed\n");
  return 0;
}