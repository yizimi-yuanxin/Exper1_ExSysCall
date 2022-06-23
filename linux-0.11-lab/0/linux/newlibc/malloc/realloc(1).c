/* Change the size of a block allocated by `malloc'.
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
#include <string.h>

#define _MALLOC_INTERNAL
#include "malloc.h"
#endif /* __ONEFILE */

#define MIN(A, B) ((A) < (B) ? (A) : (B))

/* Debugging hook for realloc.  */
PTR EXFUN((*__realloc_hook), (PTR __ptr, size_t __size));

/* Resize the given region to the new size, returning a pointer
   to the (possibly moved) region.  This is optimized for speed;
   some benchmarks seem to indicate that greater compactness is
   achieved by unconditionally allocating and copying to a
   new region.  This module has incestuous knowledge of the
   internals of both free and malloc. */
PTR
DEFUN(realloc, (ptr, size), PTR ptr AND size_t size)
{
  PTR result;
  int type;
  size_t block, blocks, oldlimit;

  if (size == 0)
    {
      free(ptr);
      return NULL;
    }
  else if (ptr == NULL)
    return malloc(size);

  if (__realloc_hook != NULL)
    return (*__realloc_hook)(ptr, size);

  block = BLOCK(ptr);

  type = _heapinfo[block].busy.type;
  switch (type)
    {
    case 0:
      /* Maybe reallocate a large block to a small fragment.  */
      if (size <= BLOCKSIZE / 2)
	{
	  result = malloc(size);
	  if (result != NULL)
	    {
	      memcpy(result, ptr, size);
	      free(ptr);
	      return result;
	    }
	}

      /* The new size is a large allocation as well;
	 see if we can hold it in place. */
      blocks = BLOCKIFY(size);
      if (blocks < _heapinfo[block].busy.info.size)
	{
	  /* The new size is smaller; return
	     excess memory to the free list. */
	  _heapinfo[block + blocks].busy.type = 0;
	  _heapinfo[block + blocks].busy.info.size
	    = _heapinfo[block].busy.info.size - blocks;
	  _heapinfo[block].busy.info.size = blocks;
	  free(ADDRESS(block + blocks));
	  result = ptr;
	}
      else if (blocks == _heapinfo[block].busy.info.size)
	/* No size change necessary.  */
	result = ptr;
      else
	{
	  /* Won't fit, so allocate a new region that will.
	     Free the old region first in case there is sufficient
	     adjacent free space to grow without moving. */
	  blocks = _heapinfo[block].busy.info.size;
	  /* Prevent free from actually returning memory to the system.  */
	  oldlimit = _heaplimit;
	  _heaplimit = 0;
	  free(ptr);
	  _heaplimit = oldlimit;
	  result = malloc(size);
	  if (result == NULL)
	    {
	      (void) malloc(blocks * BLOCKSIZE);
	      return NULL;
	    }
	  if (ptr != result)
	    memmove(result, ptr, blocks * BLOCKSIZE);
	}
      break;

    default:
      /* Old size is a fragment; type is logarithm
	 to base two of the fragment size.  */
      if (size > 1 << (type - 1) && size <= 1 << type)
	/* The new size is the same kind of fragment.  */
	result = ptr;
      else
	{
	  /* The new size is different; allocate a new space,
	     and copy the lesser of the new size and the old. */
	  result = malloc(size);
	  if (result == NULL)
	    return NULL;
	  memcpy(result, ptr, MIN(size, 1 << type));
	  free(ptr);
	}
      break;
    }

  return result;
}
