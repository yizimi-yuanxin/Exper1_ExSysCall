/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)perror.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

/*
 * Print the error indicated
 * in the cerror cell.
 */
#include <sys/types.h>
#include <sys/uio.h>

#ifdef linux
#include <string.h>
extern char *strerror(int n);
extern int writev(int handle, struct iovec *iov, int count);
#endif

extern int errno;
extern int sys_nerr;
extern char *sys_errlist[];

void
perror(char *s)
{
	struct iovec iov[4];
	register struct iovec *v = iov;

	if (s && *s) {
		v->iov_base = s;
		v->iov_len = strlen(s);
		v++;
		v->iov_base = ": ";
		v->iov_len = 2;
		v++;
	}
	v->iov_base = strerror (errno);
	v->iov_len = strlen(v->iov_base);
	v++;
	v->iov_base = "\n";
	v->iov_len = 1;
	(void) writev(2, iov, (v - iov) + 1);
}
