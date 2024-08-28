#ifndef LIBMIN_H
#define LIBMIN_H

#include "libtarg.h"

#include <stdbool.h>

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif
/* Build parameters:

   #define LIBMIN_SILENT		- disable all console messages
   #define LIBMIN_HOST		- build to run on Unix host
   #define LIBMIN_TARGET		- build to run on ARM target model

*/

#ifdef __cplusplus
extern "C" {
#endif

/* standard atol() implementation */
long libmin_atol(const char *s);
#if ALIAS_RM_LIBMIN
#define atol libmin_atol
#endif

/* standard atoi/atof implementation */
int libmin_atoi(const char *s);
#if ALIAS_RM_LIBMIN
#define atoi libmin_atoi
#endif
double libmin_atof(const char *s);
#if ALIAS_RM_LIBMIN
#define atof libmin_atof
#endif
long libmin_strtol(const char *s, char **endptr, int base);
#if ALIAS_RM_LIBMIN
#define strtol libmin_strtol
#endif

/* getopt() hooks */
extern char *optarg;
extern int optind, opterr, optopt, optpos, optreset;

/* standard getopt() implementation */
int libmin_getopt(int argc, char * const argv[], const char *optstring);
#if ALIAS_RM_LIBMIN
#define getopt libmin_getopt
#endif

/* copy src to dst, truncating or null-padding to always copy n bytes */
char *libmin_strcat(char *dest, const char *src);
#if ALIAS_RM_LIBMIN
#define strcat libmin_strcat
#endif
char *libmin_strcpy(char *dest, const char *src);
#if ALIAS_RM_LIBMIN
#define strcpy libmin_strcpy
#endif
char *libmin_strncpy(char *dst, const char *src, size_t n);
#if ALIAS_RM_LIBMIN
#define strncpy libmin_strncpy
#endif
char *libmin_strncat(char *d, const char *s, size_t n);
#if ALIAS_RM_LIBMIN
#define strncat libmin_strncat
#endif

bool libmin_strncontains(const char *str,char c, size_t n);
#if ALIAS_RM_LIBMIN
#define strncontains libmin_strncontains
#endif

bool libmin_strfits(const char *str, size_t n);
#if ALIAS_RM_LIBMIN
#define strfits libmin_strfits
#endif

/* return string length */
size_t libmin_strlen(const char *str);
#if ALIAS_RM_LIBMIN
#define strlen libmin_strlen
#endif

/* return order of strings */
int libmin_strcmp(const char *l, const char *r);
#if ALIAS_RM_LIBMIN
#define strcmp libmin_strcmp
#endif
int libmin_strncmp(const char *s1, const char *s2, size_t n);
#if ALIAS_RM_LIBMIN
#define strncmp libmin_strncmp
#endif
size_t libmin_strspn(const char *s, const char *c);
#if ALIAS_RM_LIBMIN
#define strspn libmin_strspn
#endif
char *libmin_strtok(char *s, const char *sep);
#if ALIAS_RM_LIBMIN
#define strtok libmin_strtok
#endif
char *libmin_strdup (const char *s);
#if ALIAS_RM_LIBMIN
#define strdup libmin_strdup
#endif
char *libmin_strchr(const char *s, char c);
#if ALIAS_RM_LIBMIN
#define strchr libmin_strchr
#endif
char *libmin_strrchr(const char *s, int c);
#if ALIAS_RM_LIBMIN
#define strrchr libmin_strrchr
#endif
size_t libmin_strcspn(const char *s, const char *c);
#if ALIAS_RM_LIBMIN
#define strcspn libmin_strcspn
#endif
char *libmin_strpbrk(const char *s, const char *b);
#if ALIAS_RM_LIBMIN
#define strpbrk libmin_strpbrk
#endif
char *libmin_strstr (const char *s1, const char *s2);
#if ALIAS_RM_LIBMIN
#define strstr libmin_strstr
#endif
char *libmin_strcasestr(const char *h, const char *n);
#if ALIAS_RM_LIBMIN
#define strcasestr libmin_strcasestr
#endif
int libmin_strncasecmp(const char *_l, const char *_r, size_t n);
#if ALIAS_RM_LIBMIN
#define strncasecmp libmin_strncasecmp
#endif

/* set a block of memory to a value */
void *libmin_memset(void *dest, int c, size_t n);
void *memset(void *dest, int c, size_t n);
// bu hataya sebep oluyor, memset ismi zaten baska bir dosyada kullaniliyor.
// #if ALIAS_RM_LIBMIN 
// #define memset libmin_memset
// #endif
void *libmin_memcpy(void *dest, const void *src, size_t n);
// bu hataya sebep oluyor, memset ismi zaten baska bir dosyada kullaniliyor.
// #if ALIAS_RM_LIBMIN
// #define memcpy libmin_memcpy
// #endif
int libmin_memcmp(const void *vl, const void *vr, size_t n);
#if ALIAS_RM_LIBMIN
#define memcmp libmin_memcmp
#endif
void *libmin_memmove(void *dest, const void *src, size_t n);
#if ALIAS_RM_LIBMIN
#define memmove libmin_memmove
#endif


#ifndef TARGET_SILENT
/* print a message with format FMT to the co-simulation console */
int libmin_printf(char *fmt, ...);
#if ALIAS_RM_LIBMIN
#define printf libmin_printf
#endif
#else /* TARGET_SILENT */
/* run silent */
#define libmin_printf(FMT, ARGS...)	do { ; } while (0)
#endif /* TARGET_SILENT */

int libmin_snprintf(char *buffer, size_t maxlen, const char *format, ...);
#if ALIAS_RM_LIBMIN
#define snprintf libmin_snprintf
#endif

int libmin_sprintf(char *buffer, const char *format, ...);
#if ALIAS_RM_LIBMIN
#define sprintf libmin_sprintf
#endif


/* print one character */
void libmin_putc(char c);
#if ALIAS_RM_LIBMIN
#define putc libmin_putc
#endif

/* print one string */
void libmin_puts(char *s);
#if ALIAS_RM_LIBMIN
#define puts libmin_puts
#endif

/* scan a string */
int libmin_sscanf(const char *buf, const char *fmt, ...);
#if ALIAS_RM_LIBMIN
#define sscanf libmin_sscanf
#endif

/* failure/success codes */
#define EXIT_FAILURE  1 /* failing exit status */
#define EXIT_SUCCESS  0 /* successful exit status */

/* successfully exit co-simulation */
void libmin_success(void);
#if ALIAS_RM_LIBMIN
#define success libmin_success
#endif

/* exit co-simulation with failure exit code CODE */
void libmin_fail(int code);
#if ALIAS_RM_LIBMIN
#define fail libmin_fail
#endif

void libmin_exit(int status);
#if ALIAS_RM_LIBMIN
#define exit libmin_exit
#endif


/* largest random number, must be power-of-two-minus-one! */
#define RAND_MAX (0x7fffffff)

#ifdef notdef
/* largest numbers */
#define UINT32_MAX (0xFFFFFFFFU)
#endif /* notdef */

/* see the random integer generator */
void libmin_srand(unsigned int seed);
#if ALIAS_RM_LIBMIN
#define srand libmin_srand
#endif

/* generate a random integer */
unsigned int libmin_rand(void);
#if ALIAS_RM_LIBMIN
#define rand libmin_rand
#endif

/* allocate memory */
void *libmin_malloc(size_t size);
#if ALIAS_RM_LIBMIN
#define malloc libmin_malloc
#endif
void *libmin_calloc(size_t m, size_t n);
#if ALIAS_RM_LIBMIN
#define calloc libmin_calloc
#endif
void *libmin_realloc(void *block, size_t size);
#if ALIAS_RM_LIBMIN
#define realloc libmin_realloc
#endif

/* free memory */
void libmin_free(void * addr);
#if ALIAS_RM_LIBMIN
#define free libmin_free
#endif

#ifndef __clang__
#ifndef NULL
#define NULL	((void *)0)
#endif
#endif

/* in-memory file I/O */
struct _MFILE {
  const char *fname;
  size_t data_sz;
  const uint8_t *data;
  int rdptr;
};
typedef struct _MFILE MFILE;

#define EOF (-1)

/* open an in-memory file */
MFILE* libmin_mopen(const char* fname, const char *mode);
#if ALIAS_RM_LIBMIN
#define mopen libmin_mopen
#endif

/* return in-memory file size */
size_t libmin_msize(MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define msize libmin_msize
#endif

/* at end of file */
int libmin_meof(MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define meof libmin_meof
#endif

/* close the in-memory file */
void libmin_mclose(MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define mclose libmin_mclose
#endif

/* read a buffer from the in-memory file */
size_t libmin_mread(void *ptr, size_t size, MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define mread libmin_mread
#endif

/* get a string from the in-memory file */
char *libmin_mgets(char *s, size_t size, MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define mgets libmin_mgets
#endif

/* read a character from the in-memory file */
int libmin_mgetc(MFILE *mfile);
#if ALIAS_RM_LIBMIN
#define mgetc libmin_mgetc
#endif

struct serial_output_file_t;
typedef struct serial_output_file_t SFILE;

extern SFILE *stderr;
extern SFILE *stdout;
#define stderr stderr
#define stdout stdout

SFILE *libmin_sfopen(const char *fname, const char *mode);
#if ALIAS_RM_LIBMIN
#define sfopen libmin_sfopen
#endif

int libmin_sfclose(SFILE *file);
#if ALIAS_RM_LIBMIN
#define sfclose libmin_sfclose
#endif

int libmin_sfputc(int c, SFILE *file);
#if ALIAS_RM_LIBMIN
#define sfputc libmin_sfputc
#endif

int libmin_sfputs(const char *str, SFILE *file);
#if ALIAS_RM_LIBMIN
#define sfputs libmin_sfputs
#endif

int libmin_sfprintf(SFILE *file, const char *fmt, ...);
#if ALIAS_RM_LIBMIN
#define sfprintf libmin_sfprintf
#endif

int libmin_sfflush(SFILE *file);
#if ALIAS_RM_LIBMIN
#define sfflush libmin_sfflush
#endif


#if !defined(__time_t_defined) && !defined(_TIME_T_DECLARED)
typedef	uint64_t	time_t;
#define	__time_t_defined
#define	_TIME_T_DECLARED
#endif
time_t libmin_time(time_t *timer);
#if ALIAS_RM_LIBMIN
#define time libmin_time
#endif


/* sort an array */
typedef int (*cmpfun)(const void *, const void *);
void libmin_qsort(void *base, size_t nel, size_t width, cmpfun cmp);
#if ALIAS_RM_LIBMIN && !(USE_EXTERNAL_QSORT)
#define qsort libmin_qsort
#endif


/* ctype defs */
//
// Character types
//

#define _UPPER          0x1     // Upper case letter
#define _LOWER          0x2     // Lower case letter
#define _DIGIT          0x4     // Digit[0-9]
#define _SPACE          0x8     // Tab, carriage return, newline, vertical tab or form feed
#define _PUNCT          0x10    // Punctuation character
#define _CONTROL        0x20    // Control character
#define _BLANK          0x40    // Space char
#define _HEX            0x80    // Hexadecimal digit

#define _LEADBYTE       0x8000                      // Multibyte leadbyte
#define _ALPHA          (0x0100 | _UPPER| _LOWER)   // Alphabetic character

extern unsigned short *_pctype; // pointer to table for char's

int _isctype(int c, int mask);

#define isalpha(c)     (_pctype[(int)(c)] & (_UPPER | _LOWER))
#define isupper(c)     (_pctype[(int)(c)] & _UPPER)
#define islower(c)     (_pctype[(int)(c)] & _LOWER)
#define isdigit(c)     (_pctype[(int)(c)] & _DIGIT)
#define isxdigit(c)    (_pctype[(int)(c)] & _HEX)
#define isspace(c)     (_pctype[(int)(c)] & _SPACE)
#define ispunct(c)     (_pctype[(int)(c)] & _PUNCT)
#define isalnum(c)     (_pctype[(int)(c)] & (_UPPER | _LOWER | _DIGIT))
#define isprint(c)     (_pctype[(int)(c)] & (_BLANK | _PUNCT | _UPPER | _LOWER | _DIGIT))
#define isgraph(c)     (_pctype[(int)(c)] & (_PUNCT | _UPPER | _LOWER | _DIGIT))
#define iscntrl(c)     (_pctype[(int)(c)] & _CONTROL)
#define isleadbyte(c)  (_pctype[(int)(unsigned char)(c)] & _LEADBYTE)

#define tolower(c)     (isupper(c) ? ((c) - 'A' + 'a') : (c))
#define toupper(c)     (islower(c) ? ((c) - 'a' + 'A') : (c))

/* math functions */

#define FORCE_EVAL(x) do {                        \
	if (sizeof(x) == sizeof(float)) {         \
		volatile float __x;               \
		__x = (x); (void)__x;                        \
	} else if (sizeof(x) == sizeof(double)) { \
		volatile double __x;              \
		__x = (x); (void)__x;                        \
	} else {                                  \
		volatile long double __x;         \
		__x = (x); (void)__x;                        \
	}                                         \
} while(0)

/* Get two 32 bit ints from a double.  */
#define EXTRACT_WORDS(hi,lo,d)                    \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (hi) = __u.i >> 32;                             \
  (lo) = (uint32_t)__u.i;                         \
} while (0)

/* Get the more significant 32 bit int from a double.  */
#define GET_HIGH_WORD(hi,d)                       \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (hi) = __u.i >> 32;                             \
} while (0)

/* Get the less significant 32 bit int from a double.  */
#define GET_LOW_WORD(lo,d)                        \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  (lo) = (uint32_t)__u.i;                         \
} while (0)

/* Set a double from two 32 bit ints.  */
#define INSERT_WORDS(d,hi,lo)                     \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.i = ((uint64_t)(hi)<<32) | (uint32_t)(lo);  \
  (d) = __u.f;                                    \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */
#define SET_HIGH_WORD(d,hi)                       \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  __u.i &= 0xffffffff;                            \
  __u.i |= (uint64_t)(hi) << 32;                  \
  (d) = __u.f;                                    \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */
#define SET_LOW_WORD(d,lo)                        \
do {                                              \
  union {double f; uint64_t i;} __u;              \
  __u.f = (d);                                    \
  __u.i &= 0xffffffff00000000ull;                 \
  __u.i |= (uint32_t)(lo);                        \
  (d) = __u.f;                                    \
} while (0)

/* Get a 32 bit int from a float.  */
#define GET_FLOAT_WORD(w,d)                       \
do {                                              \
  union {float f; uint32_t i;} __u;               \
  __u.f = (d);                                    \
  (w) = __u.i;                                    \
} while (0)

/* Set a float from a 32 bit int.  */
#define SET_FLOAT_WORD(d,w)                       \
do {                                              \
  union {float f; uint32_t i;} __u;               \
  __u.i = (w);                                    \
  (d) = __u.f;                                    \
} while (0)

#undef __CMPLX
#undef CMPLX
#undef CMPLXF
#undef CMPLXL

#define __CMPLX(x, y, t) \
	((union { _Complex t __z; t __xy[2]; }){.__xy = {(x),(y)}}.__z)

#define CMPLX(x, y) __CMPLX(x, y, double)
#define CMPLXF(x, y) __CMPLX(x, y, float)
#define CMPLXL(x, y) __CMPLX(x, y, long double)

#if FLT_EVAL_METHOD==0 || FLT_EVAL_METHOD==1
#define EPS DBL_EPSILON
#elif FLT_EVAL_METHOD==2
#define EPS LDBL_EPSILON
#endif

#define DBL_EPSILON 2.22044604925031308085e-16

double libmin_floor(double x);
#if ALIAS_RM_LIBMIN
#define floor libmin_floor
#endif
double libmin_scalbn(double x, int n);
#if ALIAS_RM_LIBMIN
#define scalbn libmin_scalbn
#endif
double libmin_cos(double x);
#if ALIAS_RM_LIBMIN
#define cos libmin_cos
#endif
double libmin_sin(double x);
#if ALIAS_RM_LIBMIN
#define sin libmin_sin
#endif
double fabs(double x);
double libmin_pow(double x, double y);
#if ALIAS_RM_LIBMIN
#define pow libmin_pow
#endif
double libmin_sqrt(double x);
#if ALIAS_RM_LIBMIN
#define sqrt libmin_sqrt
#endif

int libmin_abs(int i);
#if ALIAS_RM_LIBMIN
#define abs libmin_abs
#endif

/* internal mathlib interfaces */
int __rem_pio2_large(double *x, double *y, int e0, int nx, int prec);
int __rem_pio2(double x, double *y);

/* libmin assertions */
#define libmin_assert(P)    ((P) ? (void)0 : (void)libmin_fail(1))
#if ALIAS_RM_LIBMIN
#define assert libmin_assert
#endif

/* MIN/MAX functions */
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#ifdef __cplusplus
}
#endif

#endif /* LIBMIN_H */
