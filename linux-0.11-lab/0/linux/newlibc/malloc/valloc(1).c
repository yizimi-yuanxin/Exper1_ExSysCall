/* Allocate memory on a page boundary.
   Copyright 1989 Free Software Foundation
		  Written May 1989 by Mike Haertel.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   The author may be reached (Email) at the address mike@ai.mit.edu,
   or (US mail) as Mike Haertel c/o Free Software Foundation. */

#ifndef __ONEFILE
#include "ansidecl.h"
#include <stdlib.h>
#endif /* __ONEFILE */

#define pagesize 4096

PTR
DEFUN(valloc, (size), size_t size)
{
  PTR result;
  unsigned int adj;

  result = malloc(size + pagesize);
  if (result == NULL)
    return NULL;
  adj = (unsigned int) ((char *) result - (char *) NULL) % pagesize;
  if (adj != 0)
    result = (char *) result + pagesize - adj;
  return result;
}
