#define __LIBRARY__
#include <unistd.h>
#include <stdarg.h>

int open(const char * filename, int flag, ...)
{
	register int res;
	va_list arg;

	va_start(arg,flag);
#ifdef PRE_GCC_2
	__asm__("movl %0,%%ebx" : : "g" (filename) : "bx");
	__asm__("movl %0,%%ecx" : : "g" (flag));
	__asm__("movl %0,%%edx" : : "g" (va_arg(arg,int)));
	__asm__("int $0x80" :"=a" (res) :"0" (__NR_open));
#else
	__asm__("int $0x80"
		:"=a" (res)
		:"0" (__NR_open),"b" (filename),"c" (flag),
		"d" (va_arg(arg,int)));
#endif
	if (res>=0)
		return res;
	errno = -res;
	va_end(arg);
	return -1;
}
