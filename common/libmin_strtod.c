#include "libmin.h"

double libmin_strtod(const char *str, char **endptr)
{
    double result = 0.0;
    double fraction = 0.0;
    int divisor = 1;
    int sign = 1;
    int has_fraction = 0;

    // Skip leading whitespaces
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f')
        str++;

    // Check for sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Parse the integer part
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Parse the fractional part (if any)
    if (*str == '.') {
        str++;
        has_fraction = 1;
        while (*str >= '0' && *str <= '9') {
            fraction = fraction * 10.0 + (*str - '0');
            divisor *= 10;
            str++;
        }
    }

    result += fraction / divisor;

    // Handle exponent (e or E)
    if (*str == 'e' || *str == 'E') {
        int exp_sign = 1;
        int exponent = 0;

        str++;
        if (*str == '-') {
            exp_sign = -1;
            str++;
        } else if (*str == '+') {
            str++;
        }

        while (*str >= '0' && *str <= '9') {
            exponent = exponent * 10 + (*str - '0');
            str++;
        }

        if (exp_sign == -1) {
            while (exponent--) {
                result /= 10;
            }
        } else {
            while (exponent--) {
                result *= 10;
            }
        }
    }

    // Set end pointer to the character after the last parsed character
    if (endptr)
        *endptr = (char *)str;

    return result * sign;
}
