#include <string.h>
#include <time.h>
#include <sys/time.h>

/*
 * Another of these time-functions. I sure wish I knew what I am doing.
 * Linus
 */

int gettimeofday(struct timeval * tp, struct timezone * tz)
{
	tp->tv_sec = time(NULL);
	tp->tv_usec = 0;
	tz->tz_minuteswest = -120;
	tz->tz_dsttime = DST_NONE;
	return 0;
}
