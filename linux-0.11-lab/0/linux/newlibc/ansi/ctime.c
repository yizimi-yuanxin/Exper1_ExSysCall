/* mktime, localtime, gmtime */
/* written by ERS and placed in the public domain */

#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SECS_PER_MIN    (60L)
#define SECS_PER_HOUR   (60*SECS_PER_MIN)
#define SECS_PER_DAY    (24*SECS_PER_HOUR)
#define SECS_PER_YEAR   (365*SECS_PER_DAY)
#define SECS_PER_LEAPYEAR (SECS_PER_DAY + SECS_PER_YEAR)

static int days_per_mth[12] =
	{31, 28, 31, 30,
	 31, 30, 31, 31,
	 30, 31, 30, 31 };

time_t timezone = -1;	/* holds # seconds west of GMT */
static int dst = -1;	/* whether dst holds in current timezone */

/*
 * FIXME: none of these routines is very efficient. Also, none of them
 * handle dates before Jan 1, 1970.
 *
 */

/*
 * mktime: take a time structure representing the local time (such as is
 *  returned by localtime() and convert it into the standard representation
 *  (as seconds since midnight Jan. 1 1970, GMT).
 *
 */

time_t mktime(struct tm * t)
{
        time_t s;
        int y;

        y = t->tm_year - 70;
        if (y < 0)      /* year before 1970 */
                return (time_t) -1;
        s = (SECS_PER_YEAR * y) + ( ((y+1)/4) * SECS_PER_DAY);
                /* extra days for leap years */
        if ( (y+2)%4 )
                days_per_mth[1] = 28;
        else
                days_per_mth[1] = 29;

        for (y = 0; y < t->tm_mon; y++)
                s += SECS_PER_DAY * days_per_mth[y];

        s += (t->tm_mday - 1) * SECS_PER_DAY;
        s += t->tm_hour * SECS_PER_HOUR;
        s += t->tm_min * SECS_PER_MIN;
        s += t->tm_sec;
        return s;
}

static struct tm the_time;

struct tm *gmtime(const time_t *t)
{
        struct tm *stm = &the_time;
        time_t time = *t;
        int year, mday, i;

        if (time < 0)   /* negative times are bad */
                return 0;
        stm->tm_wday = ((time/SECS_PER_DAY) + 4) % 7;

        year = 70;
        for (;;) {
                if (time < SECS_PER_YEAR) break;
                if ((year % 4) == 0) {
                        if (time < SECS_PER_LEAPYEAR)
                                break;
                        else
                                time -= SECS_PER_LEAPYEAR;
                }
                else
                        time -= SECS_PER_YEAR;
                year++;
        }
        stm->tm_year = year;
        mday = stm->tm_yday = time/SECS_PER_DAY;
        days_per_mth[1] = (year % 4) ? 28 : 29;
        for (i = 0; mday >= days_per_mth[i]; i++)
                mday -= days_per_mth[i];
        stm->tm_mon = i;
        stm->tm_mday = mday + 1;
        time = time % SECS_PER_DAY;
        stm->tm_hour = time/SECS_PER_HOUR;
        time = time % SECS_PER_HOUR;
        stm->tm_min = time/SECS_PER_MIN;
        stm->tm_sec = time % SECS_PER_MIN;
        stm->tm_isdst = 0;
        return stm;
}

/* given a standard time, convert it to a local time */

struct tm *localtime(const time_t * t)
{
        struct tm *stm;
        time_t offset;  /* seconds between local time and GMT */

	if (timezone == -1) tzset();
        offset = *t - timezone;
        stm = gmtime(&offset);
	if (stm == (struct tm *)NULL) return stm; /* check for illegal time */
        stm->tm_isdst = (dst == -1) ? -1 : 0;
        return stm;
}

static const char *day[] =
{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

static const char *month[] =
	{"Jan", "Feb", "Mar", "Apr",
	 "May", "Jun", "Jul", "Aug",
	 "Sep", "Oct", "Nov", "Dec"};

char * asctime(const struct tm * time)
{
	static char buf[40];

	if (time == (struct tm *)NULL)
		strcpy(buf, "??? ??? ?? ??:??:?? ????\n");
	else
		sprintf(buf, "%.3s %.3s %2d %02d:%02d:%02d %04d\n",
		day[time->tm_wday], month[time->tm_mon], time->tm_mday,
		time->tm_hour, time->tm_min, time->tm_sec, 1900+time->tm_year);
	return(buf);
}

char *ctime(const time_t *tp)
{
        return(asctime(localtime(tp)));
}
