/* This is file TMPNAM.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)tmpnam.c	4.8 (Berkeley) 6/22/90";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/types.h>
#include <stdio.h>

#ifdef linux
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXPATHLEN	PATH_MAX

extern char *mktemp(char * template);
#endif

#ifndef P_tmpdir
#define	P_tmpdir	"/usr/tmp"
#endif

char *
tmpnam(s)
	char *s;
{
#ifndef linux
	char *malloc(), *mktemp();
#endif

	if (!s && !(s = (char *) malloc((unsigned int)MAXPATHLEN)))
		return(NULL);
	(void)sprintf(s, "%s/XXXXXX", P_tmpdir);
	return(mktemp(s));
}

char *
tempnam(dir, pfx)
	char *dir, *pfx;
{
	char *f, *name;
#ifndef linux
	char *getenv(), *malloc(), *mktemp();
#endif

	if (!(name = (char *) malloc((unsigned int)MAXPATHLEN)))
		return(NULL);

	if (f = getenv("TMPDIR")) {
		(void)sprintf(name, "%s/%sXXXXXX", f, pfx ? "" : pfx);
		if (f = mktemp(name))
			return(f);
	}
	if (dir) {
		(void)sprintf(name, "%s/%sXXXXXX", dir, pfx ? "" : pfx);
		if (f = mktemp(name))
			return(f);
	}
	(void)sprintf(name, "%s/%sXXXXXX", P_tmpdir, pfx ? "" : pfx);
	if (f = mktemp(name))
		return(f);
	(void)sprintf(name, "/tmp/%sXXXXXX", pfx ? "" : pfx);
	if (!(f = mktemp(name)))
		(void)free(name);
	return(f);
}

FILE *
tmpfile()
{
	FILE *fp;
	char *f;

	if (!(f = tmpnam((char *)NULL)) || !(fp = fopen(f, "w+"))) {
		fprintf(stderr, "tmpfile: cannot open %s.\n", f);
		return(NULL);
	}
	(void)unlink(f);
	return(fp);
}
