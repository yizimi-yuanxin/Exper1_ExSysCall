#define __LIBRARY__
#include <unistd.h>
#include <signal.h>

_syscall1(int,sigpending,sigset_t *,sigmask)
