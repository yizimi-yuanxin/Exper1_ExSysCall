#include <signal.h>
#include <unistd.h>

/*
 * More of these kind of library routines, please. Linus
 */

void abort(void)
{
	kill(getpid(), SIGABRT);
	_exit(-1);
}
