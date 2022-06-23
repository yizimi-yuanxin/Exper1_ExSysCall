/* This is file SCANF.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)scanf.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

#include	<stdio.h>
#include	<stdarg.h>

int
scanf(const char *fmt, ...)
{
	va_list ap;
	int ret;

	va_start (ap, fmt);
	ret = _doscan(stdin, fmt, (void **) ap);
	va_end (ap);
	return(ret);
}

int
fscanf(FILE *iop, const char *fmt, ...)
{
	va_list ap;
	int ret;

	va_start (ap, fmt);
	ret = _doscan(iop, fmt, (void **) ap);
	va_end (ap);
	return(ret);
}

int
sscanf(char *str, const char *fmt, ...)
{
	va_list ap;
	int ret;
	FILE _strbuf;

	_strbuf._flag = _IOREAD|_IOSTRG;
	_strbuf._ptr = _strbuf._base = str;
	_strbuf._cnt = 0;
	while (*str++)
		_strbuf._cnt++;
	_strbuf._bufsiz = _strbuf._cnt;

	va_start (ap, fmt);
	ret = _doscan(&_strbuf, fmt, (void **) ap);
	va_end (ap);
	return(ret);
}
