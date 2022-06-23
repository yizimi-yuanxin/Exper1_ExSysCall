/* This is file FTELL.C */
/* This file may have been modified by DJ Delorie (Jan 1991).  If so,
** these modifications are Coyright (C) 1991 DJ Delorie, 24 Kirsten Ave,
** Rochester NH, 03867-2954, USA.
*/

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)ftell.c	5.2 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint

/*
 * Return file offset.
 * Coordinates with buffering.
 */

#include	<stdio.h>
#ifdef linux
#include	<unistd.h>
#endif

long ftell(iop)
register FILE *iop;
{
	register long tres;
	register adjust;
#ifndef linux
	int idx;
#endif

	if (iop->_cnt < 0)
		iop->_cnt = 0;
	if (iop->_flag&_IOREAD)
	{
		adjust = - iop->_cnt;
#ifndef linux
		if (iop->_flag & _IOTEXT)            /* if a text file */
		  for (idx=-adjust-1; idx>=0; idx--) /* for every char in buf */
		    if (iop->_ptr[idx] == '\n')      /* if it's LF */
		      adjust--;                      /* there was a CR also */
#endif
	}
	else if (iop->_flag&(_IOWRT|_IORW)) {
		adjust = 0;
		if (iop->_flag&_IOWRT && iop->_base && (iop->_flag&_IONBF)==0)
		{
		  adjust = iop->_ptr - iop->_base;
#ifndef linux
		  if (iop->_flag & _IOTEXT)
		    for (idx=0; idx<adjust; idx++)
		      if (iop->_base[idx] == '\n')
		        adjust++;
#endif
		}
	} else
		return(-1);
		
	tres = lseek(fileno(iop), 0L, 1);
	if (tres<0)
		return(tres);
	tres += adjust;
	return(tres);
}
