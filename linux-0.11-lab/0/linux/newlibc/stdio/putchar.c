/* This is file PUTCHAR.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)putchar.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

/*
 * A subroutine version of the macro putchar
 */
#include <stdio.h>

#undef putchar

int
putchar(c)
register c;
{
	return (putc(c, stdout));
}
