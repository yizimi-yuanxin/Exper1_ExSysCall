#include <ctype.h>

/*
 * braindead atof.
 * Seems to work now. Linus
 */

double atof(char * s)
{
	double f = 0.0;
	int frac = 0, sign, esign, exp = 0;

	f = 0.0;
	while (isspace(*s))
		s++;
	if ((sign=(*s == '-')) || (*s == '+'))
		s++;
	while (isdigit(*s))
		f = f*10.0 + (*s++ - '0');
	if (*s == '.') {
		s++;
		while (isdigit(*s)) {
			f = f*10.0 + (*s++ - '0');
			frac++;
		}
	}
	if (toupper(*s) == 'E') {
		if ((esign=(*++s == '-')) || (*s == '+'))
			s++;
		while (isdigit(*s))
			exp = exp*10 + (*s++ - '0');
		if (esign)
			exp = -exp;
	}
	exp -= frac;
	if (exp>0)
		while (exp--)
			f *= 10.0;
	else
		while (exp++)
			f /= 10.0;
	return sign ? -f : f;
}

