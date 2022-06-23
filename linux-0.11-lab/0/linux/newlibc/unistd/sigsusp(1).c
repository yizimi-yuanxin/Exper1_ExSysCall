#define __LIBRARY__
#include <unistd.h>
#include <signal.h>

int sigsuspend(sigset_t *set)
{
	int res;

#ifdef PRE_GCC_2
	__asm__("xorl %%ebx,%%ebx" : : : "bx");
	__asm__("xorl %%ecx,%%ecx" : : : "cx");
	__asm__("movl %0,%%edx" : : "g" (*set));
	__asm__("int $0x80" :"=a" (res) :"0" (__NR_sigsuspend));
#else
	__asm__("int $0x80"
		:"=a" (res)
		:"0" (__NR_sigsuspend), "b" (0), "c" (0), "d" (*set)
		:"bx","cx");
#endif
	if (res >= 0)
		return res;
	errno = -res;
	return -1;
}
