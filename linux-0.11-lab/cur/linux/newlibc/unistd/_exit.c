#define __LIBRARY__
#include <unistd.h>

volatile void _exit(int exit_code)
{
#ifdef PRE_GCC_2
	__asm__("movl %1,%%ebx\n\t"
		"int $0x80"::"a" (__NR_exit),"g" (exit_code): "bx");
#else
	__asm__("int $0x80"::"a" (__NR_exit),"b" (exit_code));
#endif
}
