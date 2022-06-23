#include <signal.h>
#include <unistd.h>
#include <errno.h>

extern int ___sgetmask();
extern int ___ssetmask(int);

int raise(int sig)
{
	return kill(getpid(),sig);
}

int sigaddset(sigset_t *mask, int signo)
{
	if (signo >= NSIG || signo <= 0) {
		errno = EINVAL;
		return -1;
	}
	*mask |= 1<<(signo-1);
	return 1;
}

int sigdelset(sigset_t *mask, int signo)
{
	if (signo >= NSIG || signo <= 0) {
		errno = EINVAL;
		return -1;
	}
	*mask &= ~(1<<(signo-1));
	return 1;
}

int sigemptyset(sigset_t *mask)
{
	*mask = 0;
	return 1;
}

int sigfillset(sigset_t *mask)
{
	*mask = ~0;
	return 1;
}

int sigismember(sigset_t *mask, int signo)
{
	if (signo >= NSIG || signo <= 0) {
		errno = EINVAL;
		return -1;
	}
	return (*mask & (1<<(signo-1))) != 0;
}

int sigprocmask(int how, sigset_t * set, sigset_t * oset)
{
    sigset_t old;
    int rval = 0;

    old = ___sgetmask();

    if (set) switch(how) {
    case SIG_BLOCK:
	rval = ___ssetmask((*set) | old);
	break;
    case SIG_UNBLOCK:
	rval = ___ssetmask((~(*set)) & old);
	break;
    case SIG_SETMASK:
	rval = ___ssetmask(*set);
	break;
    }

    if (oset)
	*oset = old;
    return rval;
}
