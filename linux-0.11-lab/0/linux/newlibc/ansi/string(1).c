#ifndef __GNUC__
#error I want gcc!
#endif

/*
 * Quick and dirty way of getting all the string routines into the lib.
 *		Linus
 */

#define extern
#define inline
#define __LIBRARY__
#include <string.h>
