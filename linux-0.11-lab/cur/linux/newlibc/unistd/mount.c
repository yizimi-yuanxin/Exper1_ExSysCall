#define __LIBRARY__
#include <unistd.h>

_syscall3(int,mount,const char *,specialfile,const char *,dir,int,rwflag)
