#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <errno.h>

long int sysconf(int name)
{
	switch(name) {
		case _SC_ARG_MAX:
			return (long) ARG_MAX;

		case _SC_CHILD_MAX:
			return (long) CHILD_MAX;

		case _SC_CLOCKS_PER_SEC:
			return (long) CLOCKS_PER_SEC;

		case _SC_NGROUPS_MAX:
			return (long) NGROUPS_MAX;

		case _SC_OPEN_MAX:
			return (long) OPEN_MAX;

		case _SC_JOB_CONTROL:
			return -1L;			/* no job control yet */

		case _SC_SAVED_IDS:
			return -1L;			/* no saved uid/gid */

		case _SC_VERSION:
			return (long) _POSIX_VERSION;

		default:
			errno = EINVAL;
			return -1L;
	}
}
