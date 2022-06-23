#define __LIBRARY__
#include <unistd.h>

_syscall1(time_t,times,struct tms *,tms_buf)
