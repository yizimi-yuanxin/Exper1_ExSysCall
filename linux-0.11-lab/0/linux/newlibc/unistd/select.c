#define __LIBRARY__
#include <time.h>
#include <unistd.h>

int select(int nd, fd_set * in, fd_set * out, fd_set * ex, 
  struct timeval * tv)
{
	long __res;

#ifdef PRE_GCC_2
	__asm__ volatile ("movl %0,%%ebx" : : "g" ((long) &nd)
				: "bx");
	__asm__ volatile ("int $0x80" : "=a" (__res)
				: "0" (__NR_select));
#else
	__asm__ volatile ("int $0x80"
		: "=a" (__res)
		: "0" (__NR_select),"b" ((long) &nd));
#endif
	if (__res >= 0)
		return (int) __res;
	errno = -__res;
	return -1;
}
