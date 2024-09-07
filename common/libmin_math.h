#ifndef LIBMIN_MATH_H
#define LIBMIN_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

extern double acos (double);
extern double asin (double);
extern double atan2 (double, double);
extern double cosh (double);
extern double sinh (double);
extern double exp (double);
extern double ldexp (double, int);
extern double log (double);
extern double log10 (double);
// extern double pow (double, double);
// extern double sqrt (double);
extern double fmod (double, double);

extern double atan (double);
// extern double cos (double);
// extern double sin (double);
extern double tan (double);
extern double tanh (double);
extern double frexp (double, int *);
extern double modf (double, double *);
extern double ceil (double);
extern double fabs (double);
// extern double floor (double);

extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double lgamma (double);
extern double erf (double);
extern double erfc (double);
extern double log2 (double);
#if !defined(__cplusplus)
#define log2(x) (log (x) / _M_LN2)
#endif


extern double asinh (double);

#ifdef __cplusplus
}
#endif

#endif // LIBMIN_MATH_H
