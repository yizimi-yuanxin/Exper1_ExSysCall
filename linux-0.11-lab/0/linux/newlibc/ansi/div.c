#include <stdlib.h>

/*
 * Ok, there are probably buggy: sign etc. Linus
 */

div_t div(int num, int denom)
{
	div_t res;

	__asm__("idivl %3":"=a" (res.quot),"=d" (res.rem)
		:"0" (num),"g" (denom));
	return res;
}

ldiv_t ldiv(long num, long denom)
{
	ldiv_t res;

	__asm__("idivl %3":"=a" (res.quot),"=d" (res.rem)
		:"0" (num),"g" (denom));
	return res;
}

