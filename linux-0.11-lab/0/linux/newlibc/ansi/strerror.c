#include <string.h>

/*
 * Yeah, I obviously put down a lot of thinking in the error messages.
 *	Linus
 */

char * sys_errlist[] = {
	"Unknown error",
	"Not owner",
	"No such file or directory",
	"No such process",
	"Interrupted system call",
	"I/O error",
	"No such device",
	"Arg list too big",
	"Unable to exec binary file",
	"Bad file nr",
	"No children",
	"Try again",
	"Out of memory",
	"EACCES",
	"EFAULT",
	"ENOTBLK",
	"EBUSY",
	"EEXIST",
	"EXDEV",
	"ENODEV",
	"ENOTDIR",
	"EISDIR",
	"EINVAL",
	"ENFILE",
	"EMFILE",
	"ENOTTY",
	"ETXTBSY",
	"EFBIG",
	"ENOSPC",
	"ESPIPE",
	"EROFS",
	"EMLINK",
	"EPIPE",
	"EDOM",
	"ERANGE",
	"EDEADLK",
	"ENAMETOOLONG",
	"ENOLCK",
	"ENOSYS",
	"ENOTEMPTY"};

#define NR_ERRORS ((sizeof (sys_errlist))/(sizeof(char *))-1)

int sys_nerr = NR_ERRORS;

char * strerror(int n)
{
	if (n<0 || n>NR_ERRORS)
		return ("unknown error");
	return sys_errlist[n];
}

