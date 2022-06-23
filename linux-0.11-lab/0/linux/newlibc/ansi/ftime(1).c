#include <sys/timeb.h>
#include <sys/time.h>

/*
 * I simply don't know what all these time-fns should do. Linus
 */

int ftime(struct timeb * tp)
{
	time_t t;

	if (time(&t)<0)
		return -1;
	tp->time = t;
	tp->millitm = 0; 
	tp->timezone = -120;
	tp->dstflag = 0;
	return 0;
}
