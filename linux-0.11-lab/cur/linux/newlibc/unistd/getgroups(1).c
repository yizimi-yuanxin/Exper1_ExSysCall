#define __LIBRARY__
#include <unistd.h>

_syscall2(int,getgroups,int,getsetlen,gid_t *,gidset)
