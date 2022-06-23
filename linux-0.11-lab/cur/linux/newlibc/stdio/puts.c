/* This is file PUTS.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)puts.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

#include	<stdio.h>

int
puts(s)
register const char *s;
{
	register c;

	while (c = *s++)
		putchar(c);
	return(putchar('\n'));
}
