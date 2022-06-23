#define __LIBRARY__
#include <unistd.h>
#include <errno.h>

#if 1
extern long _end;

static void * ___brk_addr = &_end;
#else
void * ___brk_addr = NULL;
#endif

int brk(void * end_data_seg)
{
#ifdef PRE_GCC_2
	__asm__ volatile ("movl %0,%%ebx" : : "g" (end_data_seg): "bx");
	__asm__ volatile ("int $0x80"
		:"=a" (___brk_addr)
		:"0" (__NR_brk));
#else
	__asm__ volatile ("int $0x80"
		:"=a" (___brk_addr)
		:"0" (__NR_brk),"b" (end_data_seg));
#endif
	if (___brk_addr == end_data_seg)
		return 0;
	errno = ENOMEM;
	return -1;
}

void * sbrk(ptrdiff_t increment)
{
	void * tmp = ___brk_addr+increment;
#ifdef PRE_GCC_2
	__asm__ volatile ("movl %0,%%ebx" : : "g" (tmp): "bx");
	__asm__ volatile ("int $0x80"
		:"=a" (___brk_addr)
		:"0" (__NR_brk));
#else
	__asm__ volatile ("int $0x80"
		:"=a" (___brk_addr)
		:"0" (__NR_brk),"b" (tmp));
#endif
	if (___brk_addr == tmp)
		return tmp-increment;
	errno = ENOMEM;
	return ((void *) -1);
}
