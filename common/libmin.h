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
  #ifndef __cplusplus
    #define atol libmin_atol
  #else
    inline const auto &atol = libmin_atol;
  #endif
#endif

/* standard atoi/atof implementation */
int libmin_atoi(const char *s);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define atoi libmin_atoi
  #else
    inline const auto &atoi = libmin_atoi;
  #endif
#endif
double libmin_atof(const char *s);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define atof libmin_atof
  #else
    inline const auto &atof = libmin_atof;
  #endif
#endif
long libmin_strtol(const char *s, char **endptr, int base);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strtol libmin_strtol
  #else
    inline const auto &strtol = libmin_strtol;
  #endif
#endif

unsigned long libmin_strtoul(const char* s, char**endptr, int base);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strtoul libmin_strtoul
  #else
    inline const auto &strtoul = libmin_strtoul;
  #endif
#endif


/* getopt() hooks */
extern char *optarg;
extern int optind, opterr, optopt, optpos, optreset;

/* standard getopt() implementation */
int libmin_getopt(int argc, char * const argv[], const char *optstring);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define getopt libmin_getopt
  #else
    inline const auto &getopt = libmin_getopt;
  #endif
#endif

/* copy src to dst, truncating or null-padding to always copy n bytes */
char *libmin_strcat(char *dest, const char *src);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strcat libmin_strcat
  #else
    inline const auto &strcat = libmin_strcat;
  #endif
#endif
char *libmin_strcpy(char *dest, const char *src);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strcpy libmin_strcpy
  #else
    inline const auto &strcpy = libmin_strcpy;
  #endif
#endif
char *libmin_strncpy(char *dst, const char *src, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strncpy libmin_strncpy
  #else
    inline const auto &strncpy = libmin_strncpy;
  #endif
#endif
char *libmin_strncat(char *d, const char *s, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
  #else
  #endif

#define strncat libmin_strncat
#endif

bool libmin_strncontains(const char *str,char c, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strncontains libmin_strncontains
  #else
    inline const auto &strncontains = libmin_strncontains;
  #endif
#endif

bool libmin_strfits(const char *str, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strfits libmin_strfits
  #else
    inline const auto &strfits = libmin_strfits;
  #endif
#endif

/* return string length */
size_t libmin_strlen(const char *str);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strlen libmin_strlen
  #else
    inline const auto &strlen = libmin_strlen;
  #endif
#endif

/* return order of strings */
int libmin_strcmp(const char *l, const char *r);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strcmp libmin_strcmp
  #else
    inline const auto &strcmp = libmin_strcmp;
  #endif
#endif
int libmin_strncmp(const char *s1, const char *s2, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strncmp libmin_strncmp
  #else
    inline const auto &strncmp = libmin_strncmp;
  #endif
#endif
size_t libmin_strspn(const char *s, const char *c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strspn libmin_strspn
  #else
    inline const auto &strspn = libmin_strspn;
  #endif
#endif

char *libmin_strtok(char *s, const char *sep);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strtok libmin_strtok
  #else
    inline const auto &strtok = libmin_strtok;
  #endif
#endif
char *libmin_strdup (const char *s);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strdup libmin_strdup
  #else
    inline const auto &strdup = libmin_strdup;
  #endif
#endif
char *libmin_strchr(const char *s, char c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strchr libmin_strchr
  #else
    inline const auto &strchr = libmin_strchr;
  #endif
#endif
char *libmin_strrchr(const char *s, int c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strrchr libmin_strrchr
  #else
    inline const auto &strrchr = libmin_strrchr;
  #endif
#endif
size_t libmin_strcspn(const char *s, const char *c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strcspn libmin_strcspn
  #else
    inline const auto &strcspn = libmin_strcspn;
  #endif
#endif
char *libmin_strpbrk(const char *s, const char *b);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strpbrk libmin_strpbrk
  #else
    inline const auto &strpbrk = libmin_strpbrk;
  #endif
#endif
char *libmin_strstr (const char *s1, const char *s2);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strstr libmin_strstr
  #else
    inline const auto &strstr = libmin_strstr;
  #endif
#endif
char *libmin_strcasestr(const char *h, const char *n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define strcasestr libmin_strcasestr
  #else
    inline const auto &strcasestr = libmin_strcasestr;
  #endif
#endif
#if ALIAS_RM_LIBMIN
int libmin_strncasecmp(const char *_l, const char *_r, size_t n);
  #ifndef __cplusplus
    #define strncasecmp libmin_strncasecmp
  #else
    inline const auto &strncasecmp = libmin_strncasecmp;
  #endif
#endif

/* set a block of memory to a value */
void *libmin_memset(void *dest, int c, size_t n);
void *memset(void *dest, int c, size_t n);

void *libmin_memcpy(void *dest, const void *src, size_t n);

int libmin_memcmp(const void *vl, const void *vr, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define memcmp libmin_memcmp
  #else
    inline const auto &memcmp = libmin_memcmp;
  #endif
#endif
void *libmin_memmove(void *dest, const void *src, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define memmove libmin_memmove
  #else
    inline const auto &memmove = libmin_memmove;
  #endif
#endif


#ifndef TARGET_SILENT
/* print a message with format FMT to the co-simulation console */
int libmin_printf(char *fmt, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define printf libmin_printf
  #else
    inline const auto &printf = libmin_printf;
  #endif

#endif
#else /* TARGET_SILENT */
/* run silent */
#define libmin_printf(FMT, ARGS...)	do { ; } while (0)
#endif /* TARGET_SILENT */

#ifndef TARGET_SILENT
int libmin_vprintf(const char *fmt, va_list ap);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define vprintf libmin_vprintf
  #else
    inline const auto &vprintf = libmin_vprintf;
  #endif
#endif
#else /* TARGET_SILENT */
#define libmin_vprintf(FMT, AP)	do { ; } while (0)
#endif /* TARGET_SILENT */

int libmin_vsprintf(char *buffer, const char *format, va_list ap);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define vsprintf libmin_vsprintf
  #else
    inline const auto &vsprintf = libmin_vsprintf;
  #endif
#endif

int libmin_vsnprintf(char *buffer, size_t maxlen, const char *format, va_list ap);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define vsnprintf libmin_vsnprintf
  #else
    inline const auto &vsnprintf = libmin_vsnprintf;
  #endif
#endif

int libmin_snprintf(char *buffer, size_t maxlen, const char *format, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define snprintf libmin_snprintf
  #else
    inline const auto &snprintf = libmin_snprintf;
  #endif

#endif

int libmin_sprintf(char *buffer, const char *format, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sprintf libmin_sprintf
  #else
    inline const auto &sprintf = libmin_sprintf;
  #endif
#endif


/* print one character */
void libmin_putc(char c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define putc libmin_putc
  #else
    inline const auto &putc = libmin_putc;
  #endif
#endif

/* print one string */
void libmin_puts(char *s);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define puts libmin_puts
  #else
    inline const auto &puts = libmin_puts;
  #endif
#endif

/* scan a string */
int libmin_sscanf(const char *buf, const char *fmt, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sscanf libmin_sscanf
  #else
    inline const auto &sscanf = libmin_sscanf;
  #endif
#endif

int libmin_scanf(const char *fmt, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define scanf libmin_scanf
  #else
    inline const auto &scanf = libmin_scanf;
  #endif
#endif

int libmin_getchar(void);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define getchar libmin_getchar
  #else
    inline const auto &getchar = libmin_getchar;
  #endif
#endif

void libmin_putchar(int c);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define putchar libmin_putchar
  #else
    inline const auto &putchar = libmin_putchar;
  #endif
#endif

/* failure/success codes */
#define EXIT_FAILURE  1 /* failing exit status */
#define EXIT_SUCCESS  0 /* successful exit status */

/* successfully exit co-simulation */
void libmin_success(void);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define success libmin_success
  #else
    inline const auto &success = libmin_success;
  #endif
#endif

/* exit co-simulation with failure exit code CODE */
void libmin_fail(int code);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fail libmin_fail
  #else
    inline const auto &fail = libmin_fail;
  #endif
#endif

void libmin_abort(void);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define abort libmin_abort
  #else
  namespace std {
    inline const auto &abort = libmin_abort;
    // inline void abort() { libmin_abort(); }
  }
  #endif
#endif

void libmin_exit(int status);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define exit libmin_exit
  #else
    inline const auto &exit = libmin_exit;
  #endif
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
  #ifndef __cplusplus
    #define srand libmin_srand
  #else
    inline const auto &srand = libmin_srand;
  #endif
#endif

/* generate a random integer */
unsigned int libmin_rand(void);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define rand libmin_rand
  #else
    inline const auto &rand = libmin_rand;
  #endif
#endif

/* allocate memory */
void *libmin_malloc(size_t size);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define malloc libmin_malloc
  #else
    inline const auto &malloc = libmin_malloc;
  #endif
#endif
void *libmin_calloc(size_t m, size_t n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define calloc libmin_calloc
  #else
    inline const auto &calloc = libmin_calloc;
  #endif
#endif
void *libmin_realloc(void *block, size_t size);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define realloc libmin_realloc
  #else
    inline const auto &realloc = libmin_realloc;
  #endif
#endif

/* free memory */
void libmin_free(void * addr);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define free libmin_free
  #else
    inline const auto &free = libmin_free;
  #endif
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
  #ifndef __cplusplus
    #define mopen libmin_mopen
  #else
    inline const auto &mopen = libmin_mopen;
  #endif
#endif

/* return in-memory file size */
size_t libmin_msize(MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define msize libmin_msize
  #else
    inline const auto &msize = libmin_msize;
  #endif
#endif

/* at end of file */
int libmin_meof(MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define meof libmin_meof
  #else
    inline const auto &meof = libmin_meof;
  #endif
#endif

/* close the in-memory file */
void libmin_mclose(MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mclose libmin_mclose
  #else
    inline const auto &mclose = libmin_mclose;
  #endif
#endif

int libmin_mseek(struct _MFILE *mfile, long offset, int whence);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mseek libmin_mseek
  #else
    inline const auto &mseek = libmin_mseek;
  #endif
#endif

long libmin_mtell(MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mtell libmin_mtell
  #else
    inline const auto &mtell = libmin_mtell;
  #endif
#endif

/* read a buffer from the in-memory file */
size_t libmin_mread_bytes(void *ptr, size_t size, MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mread_bytes libmin_mread_bytes
  #else
    inline const auto &mread = libmin_mread_bytes;
  #endif
#endif

size_t libmin_mread(void *_ptr, size_t size, size_t nmemb, MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mread libmin_mread
  #else
    inline const auto &mread = libmin_mread;
  #endif
#endif


/* get a string from the in-memory file */
char *libmin_mgets(char *s, size_t size, MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mgets libmin_mgets
  #else
    inline const auto &mgets = libmin_mgets;
  #endif
#endif

/* read a character from the in-memory file */
int libmin_mgetc(MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mgetc libmin_mgetc
  #else
    inline const auto &mgetc = libmin_mgetc;
  #endif
#endif

int libmin_mungetc(int c,MFILE *mfile);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define mungetc libmin_mungetc
  #else
    inline const auto &mungetc = libmin_mungetc;
  #endif
#endif


struct serial_output_file_t;
typedef struct serial_output_file_t SFILE;


SFILE *libmin_sfopen(const char *fname, const char *mode);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfopen libmin_sfopen
  #else
    inline const auto &sfopen = libmin_sfopen;
  #endif
#endif

int libmin_sfclose(SFILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfclose libmin_sfclose
  #else
    inline const auto &sfclose = libmin_sfclose;
  #endif
#endif

int libmin_sfputc(int c, SFILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfputc libmin_sfputc
  #else
    inline const auto &sfputc = libmin_sfputc;
  #endif
#endif

int libmin_sfputs(const char *str, SFILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfputs libmin_sfputs
  #else
    inline const auto &sfputs = libmin_sfputs;
  #endif
#endif

size_t libmin_sfwrite(const void *ptr, size_t size, size_t nmemb, SFILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfwrite libmin_sfwrite
  #else
    inline const auto &sfwrite = libmin_sfwrite;
  #endif
#endif

int libmin_sfprintf(SFILE *file, const char *fmt, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfprintf libmin_sfprintf
  #else
    inline const auto &sfprintf = libmin_sfprintf;
  #endif
#endif

int libmin_vsfprintf(SFILE *file, const char *fmt, va_list ap);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define vsfprintf libmin_vsfprintf
  #else
    inline const auto &vsfprintf = libmin_vsfprintf;
  #endif
#endif

int libmin_sfflush(SFILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sfflush libmin_sfflush
  #else
    inline const auto &sfflush = libmin_sfflush;
  #endif
#endif


#if !defined(__time_t_defined) && !defined(_TIME_T_DECLARED)
typedef	uint64_t	time_t;
#define	__time_t_defined
#define	_TIME_T_DECLARED
#endif
time_t libmin_time(time_t *timer);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define time libmin_time
  #else
    inline const auto &time = libmin_time;
  #endif
#endif

double libmin_difftime (time_t _time2, time_t _time1);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define difftime libmin_difftime
  #else
    inline const auto &difftime = libmin_difftime;
  #endif
#endif


#if !(USE_EXTERNAL_QSORT)
/* sort an array */
typedef int (*cmpfun)(const void *, const void *);
void libmin_qsort(void *base, size_t nel, size_t width, cmpfun cmp);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define qsort libmin_qsort
  #else
    inline const auto &qsort = libmin_qsort;
  #endif
#endif
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
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fopen libmin_fopen
  #else
    inline const auto &fopen = libmin_fopen;
  #endif
#endif

int libmin_fclose(FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fclose libmin_fclose
  #else
    inline const auto &fclose = libmin_fclose;
  #endif
#endif

int libmin_feof(FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define feof libmin_feof
  #else
    inline const auto &feof = libmin_feof;
  #endif
#endif

int libmin_fseek(FILE *file, long offset, int whence);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fseek libmin_fseek
  #else
    inline const auto &fseek = libmin_fseek;
  #endif
#endif

long libmin_ftell(FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define ftell libmin_ftell
  #else
    inline const auto &ftell = libmin_ftell;
  #endif
#endif


size_t libmin_fread_bytes(void *ptr, size_t size, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fread_bytes libmin_fread_bytes
  #else
    inline const auto &fread_bytes = libmin_fread_bytes;
  #endif
#endif

size_t libmin_fread(void *ptr, size_t size, size_t nmemb, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fread libmin_fread
  #else
    inline const auto &fread = libmin_fread;
  #endif
#endif

char *libmin_fgets(char *s, size_t size, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fgets libmin_fgets
  #else
    inline const auto &fgets = libmin_fgets;
  #endif
#endif

int libmin_fgetc(FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fgetc libmin_fgetc
  #else
    inline const auto &fgetc = libmin_fgetc;
  #endif
#endif

int libmin_ungetc(int c, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define ungetc libmin_ungetc
  #else
    inline const auto &ungetc = libmin_ungetc;
  #endif
#endif

int libmin_fputc(int c, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fputc libmin_fputc
  #else
    inline const auto &fputc = libmin_fputc;
  #endif
#endif

int libmin_fputs(const char *str, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fputs libmin_fputs
  #else
    inline const auto &fputs = libmin_fputs;
  #endif
#endif

size_t libmin_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fwrite libmin_fwrite
  #else
    inline const auto &fwrite = libmin_fwrite;
  #endif
#endif

int libmin_fprintf(FILE *file, const char *fmt, ...);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fprintf libmin_fprintf
  #else
    inline const auto &fprintf = libmin_fprintf;
  #endif
#endif

int libmin_vfprintf(FILE *file, const char *fmt, va_list ap);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define vfprintf libmin_vfprintf
  #else
    inline const auto &vfprintf = libmin_vfprintf;
  #endif
#endif

int libmin_fflush(FILE *file);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define fflush libmin_fflush
  #else
    inline const auto &fflush = libmin_fflush;
  #endif
#endif

int libmin_system(const char *cmd);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define system libmin_system
  #else
    inline const auto &system = libmin_system;
  #endif
#endif

int libmin_unlink(const char *pathname);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define unlink libmin_unlink
  #else
    inline const auto &unlink = libmin_unlink;
  #endif
#endif

char *libmin_getcwd(char *buf, size_t size);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define getcwd libmin_getcwd
  #else
    inline const auto &getcwd = libmin_getcwd;
  #endif
#endif

int libmin_chdir(const char *path);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define chdir libmin_chdir
  #else
    inline const auto &chdir = libmin_chdir;
  #endif
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
  #ifndef __cplusplus
    #define floor libmin_floor
  #else
    inline const auto &floor = libmin_floor;
  #endif
#endif
double libmin_scalbn(double x, int n);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define scalbn libmin_scalbn
  #else
    inline const auto &scalbn = libmin_scalbn;
  #endif
#endif
double libmin_cos(double x);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define cos libmin_cos
  #else
    inline const auto &cos = libmin_cos;
  #endif
#endif
double libmin_sin(double x);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sin libmin_sin
  #else
    inline const auto &sin = libmin_sin;
  #endif
#endif
double fabs(double x);
double libmin_pow(double x, double y);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define pow libmin_pow
  #else
    inline const auto &pow = libmin_pow;
  #endif
#endif
double libmin_sqrt(double x);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define sqrt libmin_sqrt
  #else
    inline const auto &sqrt = libmin_sqrt;
  #endif
#endif

int libmin_abs(int i);
#if ALIAS_RM_LIBMIN
  #ifndef __cplusplus
    #define abs libmin_abs
  #else
    inline const auto &abs = libmin_abs;
  #endif
#endif

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
