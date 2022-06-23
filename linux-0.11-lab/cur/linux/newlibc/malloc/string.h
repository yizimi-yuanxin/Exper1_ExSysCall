/* Fake string.h supplying stuff used by malloc. */
#ifndef __ONEFILE
#include <stddef.h>
#endif

extern PTR EXFUN(memcpy, (PTR, PTR, size_t));
extern PTR EXFUN(memset, (PTR, int, size_t));
#define memmove memcpy
