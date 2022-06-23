#include <time.h>
#include <string.h>
#include <sys/time.h>

/*
 * More of these damn time-functions. I hope somebody has a complete
 * PD library out there. Linus
 */

static char tz1[1024];
static char tz2[1024];

char *tzname[2] = {
	tz1, tz2
};
extern int daylight;

/* I don't know how to implement this - the results are ... */
static char *timezone(int minutes, int dst)
{
	static char tmp[40];

	if (dst)
		minutes += 60;
	strcpy(tmp,"GMT");
	if (!minutes)
		return tmp;
	if (minutes<0) {
		tmp[3] = '-';
		minutes = -minutes;
	} else
		tmp[3] = '+';
	tmp[4] = '0'+(minutes/60);
	tmp[5] = 0;
	return tmp;
}

void tzset(void)
{
	struct timeval tp;
	struct timezone tz;

	gettimeofday(&tp, &tz);
	strcpy(tz1, timezone(tz.tz_minuteswest, 0));
	strcpy(tz2, timezone(tz.tz_minuteswest, 1));
	daylight = tz.tz_dsttime;
}
