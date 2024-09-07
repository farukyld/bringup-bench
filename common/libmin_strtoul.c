#include "libmin.h"
#include <limits.h>  // For ULONG_MAX

unsigned long libmin_strtoul(const char *nptr, char **endptr, int base) {
  unsigned long result = 0;
  unsigned long prev_result = 0;
  const char *p = nptr;

  // Skip leading white space
  while (*p == ' ' || *p == '\t')
    p++;

  // Handle optional base
  if (base == 0) {
    if (*p == '0') {
      if (p[1] == 'x' || p[1] == 'X') {
        base = 16;
        p += 2;
      } else if (*p == '0' && (p[1] >= '0' && p[1] <= '7')) {
        base = 8; // If no 'x' follows, assume base 8
        p++;
      } else {
        base = 10;
      }
    } else {
      base = 10;
    }
  } else if (base == 16) {
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
      p += 2;
    }
  }

  // If no valid digits are found, set endptr to nptr and return 0
  const char *start = p;
  while (1) {
    int digit;

    if (*p >= '0' && *p <= '9') {
      digit = *p - '0';
    } else if (*p >= 'a' && *p <= 'z') {
      digit = *p - 'a' + 10;
    } else if (*p >= 'A' && *p <= 'Z') {
      digit = *p - 'A' + 10;
    } else {
      break;
    }

    // Check if the digit is valid for the current base
    if (digit >= base)
      break;

    // Check for overflow
    prev_result = result;
    if (result > (ULONG_MAX - digit) / base) {
      result = ULONG_MAX;  // Clamp the result to ULONG_MAX on overflow
      if (endptr)
        *endptr = (char *)p;
      return result;
    }

    result = result * base + digit;
    p++;
  }

  // If no valid conversion was done, return 0 and set endptr to nptr
  if (p == start) {
    if (endptr)
      *endptr = (char *)nptr;
    return 0;
  }

  // Set endptr to where parsing stopped (first invalid character)
  if (endptr)
    *endptr = (char *)p;

  return result;
}
