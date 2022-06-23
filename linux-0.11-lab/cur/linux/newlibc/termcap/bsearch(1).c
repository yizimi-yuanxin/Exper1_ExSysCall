/* Copyright (C) 1991 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#ifdef STDC_HEADERS
#include <stdlib.h>
#else
#define NULL 0
#include <sys/types.h>
#endif

/* Perform a binary search for KEY in BASE which has NMEMB elements
   of SIZE bytes each.  The comparisons are done by (*COMPAR)().  */
char *
bsearch (key, base, nmemb, size, compar)
     register char *key;
     register char *base;
     size_t nmemb;
     register size_t size;
     register int (*compar) ();
{
  register size_t l, u, idx;
  register char *p;
  register int comparison;

  l = 0;
  u = nmemb - 1;
  while (l <= u)
    {
      idx = (l + u) / 2;
      p = (char *) (((char *) base) + (idx * size));
      comparison = (*compar) (key, p);
      /* Don't make U negative because it will wrap around.  */
      if (comparison < 0)
	{
	  if (idx == 0)
	    break;
	  u = idx - 1;
	}
      else if (comparison > 0)
	l = idx + 1;
      else
	return (char *) p;
    }

  return NULL;
}
