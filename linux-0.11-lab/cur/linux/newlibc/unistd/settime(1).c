#define __LIBRARY__
#include <unistd.h>

_syscall2(int,settimeofday,struct timeval *,tv,struct timezone *,tz)
