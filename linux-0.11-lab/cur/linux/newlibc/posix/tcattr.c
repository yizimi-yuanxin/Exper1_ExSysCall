#include <termios.h>
#include <errno.h>
#include <unistd.h>

speed_t cfgetispeed(struct termios *termios_p);
speed_t cfgetospeed(struct termios *termios_p);

int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);

int tcdrain(int fildes);
int tcflow(int fildes, int action);
int tcflush(int fildes, int queue_selector);
int tcsendbreak(int fildes, int duration);

int tcgetattr(int fildes, struct termios *termios_p)
{
	return ioctl(fildes, TCGETS, termios_p);
}

int tcsetattr(int fildes, int optional_actions, struct termios *termios_p)
{
	switch(optional_actions) {
		case TCSANOW:
			return ioctl(fildes, TCSETS, termios_p);
		case TCSADRAIN:
			return ioctl(fildes, TCSETSW, termios_p);
		case TCSAFLUSH:
			return ioctl(fildes, TCSETSF, termios_p);
		default:
			errno = EINVAL;
			return -1;
	}
}
