#include <sys/types.h>
#include <unistd.h>
#include <termios.h>

pid_t tcgetpgrp(int fildes)
{
	int tmp;

	if (ioctl(fildes,TIOCGPGRP,&tmp)<0)
		return -1;
	return tmp;
}

int tcsetpgrp(int fildes, pid_t pgid)
{
	int tmp=pgid;

	return ioctl(fildes,TIOCSPGRP,&tmp);
}
