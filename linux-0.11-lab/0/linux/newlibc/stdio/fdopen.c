/* This is file FDOPEN.C */
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
static char sccsid[] = "@(#)fdopen.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

/*
 * Unix routine to do an "fopen" on file descriptor
 * The mode has to be repeated because you can't query its
 * status
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>

#ifdef linux
#include <unistd.h>
#endif

extern FILE *_findiop();

FILE *
fdopen(int fd, const char *mode)
{
	static int nofile = -1;
	register FILE *iop;
#ifndef linux
	int new_mode = _fmode;
#endif

	if (nofile < 0)
		nofile = getdtablesize();

	if (fd < 0 || fd >= nofile)
		return (NULL);

	iop = _findiop();
	if (iop == NULL)
		return (NULL);

	iop->_cnt = 0;
	iop->_file = fd;
	iop->_bufsiz = 0;
	iop->_base = iop->_ptr = NULL;

	switch (*mode) {
	case 'r':
		iop->_flag = _IOREAD;
		break;
	case 'a':
		lseek(fd, (off_t)0, L_XTND);
		/* fall into ... */
	case 'w':
		iop->_flag = _IOWRT;
		break;
	default:
		return (NULL);
	}

#ifdef linux
	if (mode[1] == '+')
		iop->_flag = _IORW;
#else
	if (mode[1] == '+')
	{
		iop->_flag = _IORW;
		mode++;
	}
	if (mode[1] == 't')
	{
		iop->_flag |= _IOTEXT;
		new_mode = O_TEXT;
	}
	if (mode[1] == 'b')
	{
		new_mode = O_BINARY;
	}
	setmode(fd, new_mode);
#endif

	return (iop);
}
