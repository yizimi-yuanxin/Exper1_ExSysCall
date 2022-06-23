/* This file has been modified by Hongjiu Lu (Feb 1992).
 */

/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Sean Eric Fagan
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the University of California, Berkeley and its contributors''
 * in the documentation or other materials provided with the distribution
 * and in all advertising materials mentioning features or use of this
 * software. Neither the name of the University nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef SOFT_387

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)modf.c	5.1 (Berkeley) 4/23/90";
#endif /* LIBC_SCCS and not lint */

/*
 * modf(value, iptr): return fractional part of value, and stores the
 * integral part into iptr (a pointer to double).
 *
 * Written by Sean Eric Fagan (sef@kithrup.COM)
 * Sun Mar 11 20:27:30 PST 1990
 */

/* With CHOP mode on, frndint behaves as TRUNC does.  Useful. */
double
modf(double value, double *iptr)
{
	double temp;
	volatile short i87flag, i87temp;
	__asm ("fnstcw %0" : "=m" (i87flag) : );
	i87temp = i87flag | 0xc00 ; /* turn on chop mode [truncation] */
	__asm ("fldcw %0" : : "m" (i87temp));
#ifdef PRE_GCC_2
	__asm ("frndint" : "=t" (temp) : "0" (value)); /* temp = int of value */
#else
	__asm ("frndint" : "=f" (temp) : "0" (value)); /* temp = int of value */
#endif
	__asm ("fldcw %0" : : "m" (i87flag));
	*iptr = temp;
	return (value - temp);
}

#else

#include "soft.h"

#define shiftleft(dp,n)	{	/* n = 0 to 32 */ \
	dp->mant1 = ((dp->mant1 << (n)) + (dp->mant2 >> (32-(n)))) \
		& 0x0FFFFF; dp->mant2 <<= (n); dp->exp -= (n); }


/*  Returns fractional part of d, stores integer part in *integ
 */
double modf(double d, double *integ)
{
    struct bitdouble *dp = (struct bitdouble *)&d;
    struct bitdouble *ip = (struct bitdouble *)integ;
    int e = dp->exp - BIAS;

    if (e < 0) {		/* no integer part */
	*integ = 0;
	return d;
    }

    /* compute integer: clear fractional part where necessary 
     */
    *integ = d;
    if (e <= 20) {
	ip->mant1 &= (-1L << (20-e));		/* split in mant1... */
	ip->mant2 = 0;
    }
    else 
      if (e <= 52) 
	ip->mant2 &= (-1L << (52-e));		/* split in mant2 */
      else return 0;				/* no fractional part */

    /* compute fractional part: shift left over integer part
     */
    if (e)
      if (e <= 32)
	shiftleft(dp,e)
      else {
	dp->mant1 = (dp->mant2 << (e-32)) & 0x0FFFFF;
	dp->mant2 = 0;
	dp->exp -= e;
      }

    /* adjust fractional part shifting left... 
     */
    if (dp->mant1==0 && dp->mant2==0)	/* fraction is zero */
	return 0;

    while (!(dp->mant1 & 0x080000)) 	/* stack to the left */
	shiftleft(dp,1);

    shiftleft(dp,1);			/* lose 'invisible bit' */
    return d;
}
#endif
