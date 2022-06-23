/* The <math.h> header contains prototypes for mathematical functions. */

#ifndef _MATH_H
#define _MATH_H

#define HUGE_VAL   9.9e+307

extern double acos(double x);
extern double asin(double x);
extern double atan(double x);
extern double atan2(double y, double x);
extern double ceil(double x);
extern double cos(double x);
extern double cosh(double x);
extern double exp(double x);
extern double fabs(double x);
extern double floor(double x);
extern double fmod(double x, double y);
extern double frexp(double x, int *exp);
extern double ldexp(double x, int exp);
extern double log(double x);
extern double log10(double x);
extern double modf(double x, double *iptr);
extern double pow(double x, double y);
extern double sin(double x);
extern double sinh(double x);
extern double sqrt(double x);
extern double tan(double x);
extern double tanh(double x);

extern int isinf (double);
extern int isnan (double);
extern double erf (double x);
extern double erfc (double x);
extern double j0 (double x);
extern double j1 (double x);
extern double jn (int n, double x);
extern double lgamma (double x);
extern double y0 (double x);
extern double y1 (double x);
extern double yn (int n, double x);

#ifndef __LIBRARY__
extern int signgam;
#endif

#endif /* _MATH_H */
