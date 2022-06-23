#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

/*
 * strtoul etc... Hope it works. Linus
 */

/* ok, this isn't portable, but it works */

#define do_mul(base,result,overflow) \
__asm__("mull %3":"=a" (result),"=d" (overflow):"0" (result),"g" (base))

#define NUM(c) (isdigit(c)?c-'0':islower(c)?c-'a'+10:isupper(c)?c-'A'+10:127)

static unsigned long _strtoul(const char * s, char **endp, int base)
{
	unsigned long overflow,num,result;

	if (!base)
		if (*s=='0')
			if (toupper(s[1])=='X')
				base=16;
			else
				base=8;
		else
			base=10;
	if (base == 16 && *s=='0' && toupper(s[1])=='X')
		s += 2;
	overflow = 1;		/* forces error if no while */
	result = 0;
	while ((num=NUM(*s))<base) {
		s++;
		do_mul(base,result,overflow);
		if ((result += num)<num)
			overflow=1;
		if (overflow) break;
	}
	if (overflow) {
		result = ULONG_MAX;
		errno = ERANGE;
	}
	*endp = (char *) s;
	return result;
}

long strtol(const char * s, char **endp, int base)
{
	int sign;
	unsigned long result;
	char * tmp;

	if (!endp)		/* tmp is never really used, this just */
		endp = &tmp;	/* is a hack so that we never have to check */
	*endp = (char *) s;
	if (base<0 || base==1 || base>36)
		return LONG_MAX;
	while (isspace(*s))
		s++;
	*endp = (char *) s;
	if (sign=(*s=='-'))
		s++;
	result = _strtoul(s,endp,base);
	if (!sign && result > (unsigned) LONG_MAX) {
		errno = ERANGE;
		return LONG_MAX;
	} else if (sign && result > (unsigned) LONG_MAX+1) {
		errno = ERANGE;
		return LONG_MIN;
	}
	return sign?-result:result;
}

unsigned long strtoul(const char * s, char **endp, int base)
{
	char * tmp;

	if (!endp)		/* tmp is never really used, this just */
		endp = &tmp;	/* is a hack so that we never have to check */
	*endp = (char *) s;
	if (base<0 || base==1 || base>36) {
		errno = ERANGE;
		return ULONG_MAX;
	}
	while (isspace(*s))
		s++;
	*endp = (char *) s;
	return _strtoul(s,endp,base);
}		

