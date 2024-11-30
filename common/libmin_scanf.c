#include "libmin.h"
#include "libtarg.h"

#define MAXLN 1024
#define SPACE "\t\n\f\r "

int libmin_scanf(const char* fmt, ...)
{
  libmin_printf("libmin_scanf not implemented\n");
  libmin_exit(1);
  return 0;
}

strong_alias(libmin_scanf, scanf);

int
libmin_sscanf(const char *buf, const char *fmt, ...)
{
  va_list vl;
  int i, j = 0, ret = 0;
  char *out_loc;

  va_start(vl, fmt);

  i = 0;
  while (fmt && fmt[i] && buf[j])
  {
    if (fmt[i] == '%') 
    {
      i++;
      int is_long = 0;

      // Check if the next character is 'l' for long specifiers
      if (fmt[i] == 'l') {
        is_long = 1;
        i++;
      }

      switch (fmt[i]) 
      {
        case 'c': 
        {
          if (is_long) {
            // 'l' modifier with 'c' doesn't make sense, handle error
            libmin_printf("Invalid format: 'l' modifier cannot be used with 'c'\n");
            libmin_exit(1);
          }
          *(char *)va_arg(vl, char*) = buf[j];
          j++;
          ret++;
          break;
        }
        case 'd': 
        {
          if (is_long) {
            *(long *)va_arg(vl, long*) = libmin_strtol(&buf[j], &out_loc, 10);
          } else {
            *(int *)va_arg(vl, int*) = libmin_strtol(&buf[j], &out_loc, 10);
          }
          j += (out_loc - &buf[j]);
          ret++;
          break;
        }
        case 'x': 
        {
          if (is_long) {
            *(long *)va_arg(vl, long*) = libmin_strtol(&buf[j], &out_loc, 16);
          } else {
            *(int *)va_arg(vl, int*) = libmin_strtol(&buf[j], &out_loc, 16);
          }
          j += (out_loc - &buf[j]);
          ret++;
          break;
        }
        case 'f': 
        {
          if (is_long) {
            // Handle %lf (double)
            *(double *)va_arg(vl, double*) = libmin_strtod(&buf[j], &out_loc);
          } else {
            // Handle %f (float)
            *(float *)va_arg(vl, float*) = (float)libmin_strtod(&buf[j], &out_loc);
          }
          j += (out_loc - &buf[j]);
          ret++;
          break;
        }
        default:
        {
          // Handle unsupported formats gracefully
          libmin_printf("Unsupported format: %%%c\n", fmt[i]);
          libmin_exit(1);
          break;
        }
      }
    } 
    else 
    {
      // If not a format specifier, ensure buf[j] matches fmt[i]
      if (fmt[i] != buf[j]) {
        // If they don't match, return failure or an error
        libmin_printf("Input does not match format at position %d: expected '%c', got '%c'\n", j, fmt[i], buf[j]);
        libmin_exit(1);
      }
      j++; // Move to the next character in the buffer
    }
    i++; // Move to the next format character
  }

  va_end(vl);
  return ret;
}

strong_alias(libmin_sscanf, sscanf);
