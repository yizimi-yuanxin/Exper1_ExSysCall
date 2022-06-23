#define __LIBRARY__
#include <unistd.h>

_syscall3(int,lseek,int,fildes,off_t,offset,int,origin)
