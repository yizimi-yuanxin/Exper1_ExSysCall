#include <unistd.h>
#include <termios.h>

/*
 * Simple isatty for Linux.
 */

int isatty(int fd)
{
	struct termios tmp;

	if (ioctl(fd,TCGETS,&tmp)<0)
		return (0);
	return 1;
}
