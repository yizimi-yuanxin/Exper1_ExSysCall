/* This is file FLSBUF.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)flsbuf.c	5.5 (Berkeley) 6/18/90";
#endif LIBC_SCCS and not lint

#include	<stdio.h>
#include	<sys/types.h>

#ifdef linux
#include <stdlib.h>
#include <unistd.h>

extern int isatty (int);
extern void _fwalk(int (*) ());

#else
#include	<sys/stat.h>
char	*malloc();
#endif


int
_flsbuf(unsigned int c, register FILE *iop)
{
	register char *base;
	register n, rn;
	char c1;
	int size;
#ifndef linux
	struct stat stbuf;
#endif

	if (iop->_flag & _IORW) {
		iop->_flag |= _IOWRT;
		iop->_flag &= ~(_IOEOF|_IOREAD);
	}

	if ((iop->_flag&_IOWRT)==0)
		return(EOF);
tryagain:
	if (iop->_flag&_IOLBF) {
		base = iop->_base;
		*iop->_ptr++ = c;
		if ((rn = iop->_ptr - base) >= iop->_bufsiz || c == '\n') {
			iop->_ptr = base;
			iop->_cnt = 0;
		} else {
			/* we got here because _cnt is wrong, so fix it */
			iop->_cnt = -rn;
			rn = n = 0;
		}
	} else if (iop->_flag&_IONBF) {
		c1 = c;
		rn = 1;
		base = &c1;
		iop->_cnt = 0;
	} else {
		if ((base=iop->_base)==NULL) {
#ifdef linux
			size = BUFSIZ;
#else
			if (fstat(fileno(iop), &stbuf) < 0 ||
			    stbuf.st_blksize <= NULL)
				size = BUFSIZ;
			else
				size = stbuf.st_blksize;
#endif
			if ((iop->_base=base=malloc(size)) == NULL) {
				iop->_flag |= _IONBF;
				goto tryagain;
			}
			iop->_flag |= _IOMYBUF;
			iop->_bufsiz = size;
			if (iop==stdout && isatty(fileno(stdout))) {
				iop->_flag |= _IOLBF;
				iop->_ptr = base;
				goto tryagain;
			}
			rn = n = 0;
		} else
			rn = iop->_ptr - base;
		iop->_ptr = base;
		iop->_cnt = iop->_bufsiz;
	}
	while (rn > 0) {
		n = write(fileno(iop), base, rn);
		if (n <= 0) {
			iop->_flag |= _IOERR;
			return(EOF);
		}
		rn -= n;
		base += n;
	}
	if ((iop->_flag&(_IOLBF|_IONBF)) == 0) {
		iop->_cnt--;
		*iop->_ptr++ = c;
	}
	return(c);
}

int
fpurge(register FILE *iop)
{
	iop->_ptr = iop->_base;
	iop->_cnt = iop->_flag&(_IOLBF|_IONBF|_IOREAD) ? 0 : iop->_bufsiz;
	return(0);
}

int
fflush(register FILE *iop)
{
	register char *base;
	register n, rn;

	if ((iop->_flag&(_IONBF|_IOWRT))==_IOWRT &&
	    (base = iop->_base) != NULL && (rn = n = iop->_ptr - base) > 0) {
		iop->_ptr = base;
		iop->_cnt = (iop->_flag&(_IOLBF|_IONBF)) ? 0 : iop->_bufsiz;
		do {
		        n = write(fileno(iop), base, rn);
			if (n <= 0) {
				iop->_flag |= _IOERR;
				return(EOF);
			}
			rn -= n;
			base += n;
		} while (rn > 0);
	}
	return(0);
}

int
fclose(register FILE *iop)
{
	register int r;

	r = EOF;
	if (iop->_flag&(_IOREAD|_IOWRT|_IORW) && (iop->_flag&_IOSTRG)==0) {
		r = fflush(iop);
		if (close(fileno(iop)) < 0)
			r = EOF;
		if (iop->_flag&_IOMYBUF)
			free(iop->_base);
	}
	iop->_cnt = 0;
	iop->_base = (char *)NULL;
	iop->_ptr = (char *)NULL;
	iop->_bufsiz = 0;
	iop->_flag = 0;
	iop->_file = 0;
	return(r);
}

void
_cleanup()
{

	_fwalk(fclose);
}
