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

#ifdef ALIAS_RM_LIBMIN
#define strong_alias(name, aliasname) _strong_alias(name, aliasname)
#define _strong_alias(name, aliasname) \
  extern __typeof (name) aliasname __attribute__ ((alias (#name)));

#define declare_alias(name, aliasname) _declare_alias(name, aliasname)
#define _declare_alias(name, aliasname) \
  extern __typeof (name) aliasname;
#else
#define strong_alias(name, aliasname)
#define declare_alias(name, aliasname)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* standard atol() implementation */
long libmin_atol(const char *s);
declare_alias(libmin_atol, atol)

/* standard atoi/atof implementation */
int libmin_atoi(const char *s);
declare_alias(libmin_atoi, atoi)

double libmin_atof(const char *s);
declare_alias(libmin_atof, atof)

long libmin_strtol(const char *s, char **endptr, int base);
declare_alias(libmin_strtol, strtol)

unsigned long libmin_strtoul(const char* s, char**endptr, int base);
declare_alias(libmin_strtoul, strtoul)

/* getopt() hooks */
extern char *optarg;
extern int optind, opterr, optopt, optpos, optreset;

/* standard getopt() implementation */
int libmin_getopt(int argc, char * const argv[], const char *optstring);
declare_alias(libmin_getopt, getopt)

/* copy src to dst, truncating or null-padding to always copy n bytes */
char *libmin_strcat(char *dest, const char *src);
declare_alias(libmin_strcat, strcat)

char *libmin_strcpy(char *dest, const char *src);
declare_alias(libmin_strcpy, strcpy)

char *libmin_strncpy(char *dst, const char *src, size_t n);
declare_alias(libmin_strncpy, strncpy)

char *libmin_strncat(char *d, const char *s, size_t n);
declare_alias(libmin_strncat, strncat)

bool libmin_strncontains(const char *str,char c, size_t n);
declare_alias(libmin_strncontains, strncontains)

bool libmin_strfits(const char *str, size_t n);
declare_alias(libmin_strfits, strfits)

/* return string length */
size_t libmin_strlen(const char *str);
declare_alias(libmin_strlen, strlen)

/* return order of strings */
int libmin_strcmp(const char *l, const char *r);
declare_alias(libmin_strcmp, strcmp)

int libmin_strncmp(const char *s1, const char *s2, size_t n);
declare_alias(libmin_strncmp, strncmp)

size_t libmin_strspn(const char *s, const char *c);
declare_alias(libmin_strspn, strspn)

char *libmin_strtok(char *s, const char *sep);
declare_alias(libmin_strtok, strtok)

char *libmin_strdup (const char *s);
declare_alias(libmin_strdup, strdup)

char *libmin_strchr(const char *s, char c);
declare_alias(libmin_strchr, strchr)

char *libmin_strrchr(const char *s, int c);
declare_alias(libmin_strrchr, strrchr)

size_t libmin_strcspn(const char *s, const char *c);
declare_alias(libmin_strcspn, strcspn)

char *libmin_strpbrk(const char *s, const char *b);
declare_alias(libmin_strpbrk, strpbrk)

char *libmin_strstr (const char *s1, const char *s2);
declare_alias(libmin_strstr, strstr)

char *libmin_strcasestr(const char *h, const char *n);
declare_alias(libmin_strcasestr, strcasestr)

/* set a block of memory to a value */
void *libmin_memset(void *dest, int c, size_t n);
declare_alias(libmin_memset, memset)

void *libmin_memcpy(void *dest, const void *src, size_t n);
declare_alias(libmin_memcpy, memcpy)

int libmin_memcmp(const void *vl, const void *vr, size_t n);
declare_alias(libmin_memcmp, memcmp)

void *libmin_memmove(void *dest, const void *src, size_t n);
declare_alias(libmin_memmove, memmove)

/* print a message with format FMT to the co-simulation console */
int libmin_printf(char *fmt, ...);
declare_alias(libmin_printf, printf)

int libmin_vprintf(const char *fmt, va_list ap);
declare_alias(libmin_vprintf, vprintf)

int libmin_vsprintf(char *buffer, const char *format, va_list ap);
declare_alias(libmin_vsprintf, vsprintf)

int libmin_vsnprintf(char *buffer, size_t maxlen, const char *format, va_list ap);
declare_alias(libmin_vsnprintf, vsnprintf)

int libmin_snprintf(char *buffer, size_t maxlen, const char *format, ...);
declare_alias(libmin_snprintf, snprintf)

int libmin_sprintf(char *buffer, const char *format, ...);
declare_alias(libmin_sprintf, sprintf)

/* print one character */
void libmin_putc(char c);
declare_alias(libmin_putc, putc)

/* print one string */
void libmin_puts(char *s);
declare_alias(libmin_puts, puts)

/* scan a string */
int libmin_sscanf(const char *buf, const char *fmt, ...);
declare_alias(libmin_sscanf, sscanf)

int libmin_scanf(const char *fmt, ...);
declare_alias(libmin_scanf, scanf)

int libmin_getchar(void);
declare_alias(libmin_getchar, getchar)

void libmin_putchar(int c);
declare_alias(libmin_putchar, putchar)

/* failure/success codes */
#define EXIT_FAILURE  1 /* failing exit status */
#define EXIT_SUCCESS  0 /* successful exit status */

/* successfully exit co-simulation */
void libmin_success(void);
declare_alias(libmin_success, success)

/* exit co-simulation with failure exit code CODE */
void libmin_fail(int code);
declare_alias(libmin_fail, fail)

void libmin_abort(void);
// abort'la ilgili farkli bir durum olabilir, libgcc'de std::abort olarak kullniliyor cunku.
// declare_alias(libmin_abort, abort)

void libmin_exit(int status);
declare_alias(libmin_exit, exit)

/* largest random number, must be power-of-two-minus-one! */
#define RAND_MAX (0x7fffffff)

#ifdef notdef
/* largest numbers */
#define UINT32_MAX (0xFFFFFFFFU)
#endif /* notdef */

/* see the random integer generator */
void libmin_srand(unsigned int seed);
declare_alias(libmin_srand, srand)

/* generate a random integer */
unsigned int libmin_rand(void);
declare_alias(libmin_rand, rand)

/* allocate memory */
extern void *libmin_malloc(size_t size);
declare_alias(libmin_malloc, malloc)

void *libmin_calloc(size_t m, size_t n);
declare_alias(libmin_calloc, calloc)

void *libmin_realloc(void *block, size_t size);
declare_alias(libmin_realloc, realloc)

/* free memory */
void libmin_free(void * addr);
declare_alias(libmin_free, free)

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
declare_alias(libmin_mopen, mopen)

/* return in-memory file size */
size_t libmin_msize(MFILE *mfile);
declare_alias(libmin_msize, msize)

/* at end of file */
int libmin_meof(MFILE *mfile);
declare_alias(libmin_meof, meof)

/* close the in-memory file */
void libmin_mclose(MFILE *mfile);
declare_alias(libmin_mclose, mclose)

int libmin_mseek(struct _MFILE *mfile, long offset, int whence);
declare_alias(libmin_mseek, mseek)

long libmin_mtell(MFILE *mfile);
declare_alias(libmin_mtell, mtell)

/* read a buffer from the in-memory file */
size_t libmin_mread_bytes(void *ptr, size_t size, MFILE *mfile);
declare_alias(libmin_mread_bytes, mread_bytes)

size_t libmin_mread(void *_ptr, size_t size, size_t nmemb, MFILE *mfile);
declare_alias(libmin_mread, mread)

/* get a string from the in-memory file */
char *libmin_mgets(char *s, size_t size, MFILE *mfile);
declare_alias(libmin_mgets, mgets)

/* read a character from the in-memory file */
int libmin_mgetc(MFILE *mfile);
declare_alias(libmin_mgetc, mgetc)

int libmin_mungetc(int c,MFILE *mfile);
declare_alias(libmin_mungetc, mungetc)

struct serial_output_file_t;
typedef struct serial_output_file_t SFILE;


SFILE *libmin_sfopen(const char *fname, const char *mode);
declare_alias(libmin_sfopen, sfopen)

int libmin_sfclose(SFILE *file);
declare_alias(libmin_sfclose, sfclose)

int libmin_sfputc(int c, SFILE *file);
declare_alias(libmin_sfputc, sfputc)

int libmin_sfputs(const char *str, SFILE *file);
declare_alias(libmin_sfputs, sfputs)

size_t libmin_sfwrite(const void *ptr, size_t size, size_t nmemb, SFILE *file);
declare_alias(libmin_sfwrite, sfwrite)

int libmin_sfprintf(SFILE *file, const char *fmt, ...);
declare_alias(libmin_sfprintf, sfprintf)

int libmin_vsfprintf(SFILE *file, const char *fmt, va_list ap);
declare_alias(libmin_vsfprintf, vsfprintf)

int libmin_sfflush(SFILE *file);
declare_alias(libmin_sfflush, sfflush)

#if !defined(__time_t_defined) && !defined(_TIME_T_DECLARED)
typedef	uint64_t	time_t;
#define	__time_t_defined
#define	_TIME_T_DECLARED
#endif
time_t libmin_time(time_t *timer);
declare_alias(libmin_time, time)

double libmin_difftime (time_t _time2, time_t _time1);
declare_alias(libmin_difftime, difftime)

#if !(USE_EXTERNAL_QSORT)
/* sort an array */
typedef int (*cmpfun)(const void *, const void *);
void libmin_qsort(void *base, size_t nel, size_t width, cmpfun cmp);
declare_alias(libmin_qsort, qsort)
#endif

// mfile ve sfile icin cevreleyici
struct file_t;
typedef struct file_t FILE;

extern FILE *stdin;
#define stdin stdin

extern FILE *stderr;
extern FILE *stdout;
#define stderr stderr
#define stdout stdout

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

FILE *libmin_fopen(const char *fname, const char *mode_str);
declare_alias(libmin_fopen, fopen)

int libmin_fclose(FILE *file);
declare_alias(libmin_fclose, fclose)

int libmin_feof(FILE *file);
declare_alias(libmin_feof, feof)

int libmin_fseek(FILE *file, long offset, int whence);
declare_alias(libmin_fseek, fseek)

long libmin_ftell(FILE *file);
declare_alias(libmin_ftell, ftell)

size_t libmin_fread_bytes(void *ptr, size_t size, FILE *file);
declare_alias(libmin_fread_bytes, fread_bytes)

size_t libmin_fread(void *ptr, size_t size, size_t nmemb, FILE *file);
declare_alias(libmin_fread, fread)

char *libmin_fgets(char *s, size_t size, FILE *file);
declare_alias(libmin_fgets, fgets)

int libmin_fgetc(FILE *file);
declare_alias(libmin_fgetc, fgetc)

int libmin_ungetc(int c, FILE *file);
declare_alias(libmin_ungetc, ungetc)

int libmin_fputc(int c, FILE *file);
declare_alias(libmin_fputc, fputc)

int libmin_fputs(const char *str, FILE *file);
declare_alias(libmin_fputs, fputs)

size_t libmin_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *file);
declare_alias(libmin_fwrite, fwrite)

int libmin_fprintf(FILE *file, const char *fmt, ...);
declare_alias(libmin_fprintf, fprintf)

int libmin_vfprintf(FILE *file, const char *fmt, va_list ap);
declare_alias(libmin_vfprintf, vfprintf)

int libmin_fflush(FILE *file);
declare_alias(libmin_fflush, fflush)

int libmin_system(const char *cmd);
declare_alias(libmin_system, system)

int libmin_unlink(const char *pathname);
declare_alias(libmin_unlink, unlink)

char *libmin_getcwd(char *buf, size_t size);
declare_alias(libmin_getcwd, getcwd)

int libmin_chdir(const char *path);
declare_alias(libmin_chdir, chdir)

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
declare_alias(libmin_floor, floor)

double libmin_scalbn(double x, int n);
declare_alias(libmin_scalbn, scalbn)

double libmin_cos(double x);
declare_alias(libmin_cos, cos)

double libmin_sin(double x);
declare_alias(libmin_sin, sin)

double fabs(double x);
declare_alias(fabs, libmin_fabs)

double libmin_pow(double x, double y);
declare_alias(libmin_pow, pow)

double libmin_sqrt(double x);
declare_alias(libmin_sqrt, sqrt)

int libmin_abs(int i);
declare_alias(libmin_abs, abs)

/* internal mathlib interfaces */
int __rem_pio2_large(double *x, double *y, int e0, int nx, int prec);
int __rem_pio2(double x, double *y);

/* libmin assertions */
#define libmin_assert(P)    ((P) ? (void)0 : (void)libmin_fail(1))
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define assert libmin_assert
  #else
    #define assert libmin_assert
  #endif

#endif

/* MIN/MAX functions */
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

#ifdef __cplusplus
}
#endif

#endif /* LIBMIN_H */
