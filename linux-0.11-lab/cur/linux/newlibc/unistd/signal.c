#define __LIBRARY__
#include <unistd.h>
#include <signal.h>

extern void ___sig_restore();
extern void ___masksig_restore();

int ___ssetmask(int mask)
{
	long res;
#ifdef PRE_GCC_2
	__asm__("movl %0,%%ebx" : : "g" (mask) : "bx");
	__asm__("int $0x80" :"=a" (res) :"0" (__NR_ssetmask));
#else
	__asm__("int $0x80":"=a" (res)
		:"0" (__NR_ssetmask),"b" (mask));
#endif
	return res;
}

int ___sgetmask(void)
{
	long res;
	__asm__("int $0x80":"=a" (res)
		:"0" (__NR_sgetmask));
	return res;
}

void (*signal(int sig, void (*func)(int)))(int)
{
	void (*res)();

#ifdef PRE_GCC_2
	__asm__("movl %0,%%ebx" : : "g" (sig) : "bx");
	__asm__("movl %0,%%ecx" : : "g" (func));
	__asm__("movl %0,%%edx" : : "g" ((long)___sig_restore));
	__asm__("int $0x80" :"=a" (res) :"0" (__NR_signal));
#else
	__asm__("int $0x80":"=a" (res):
	"0" (__NR_signal),"b" (sig),"c" (func),"d" ((long)___sig_restore));
#endif
	return res;
}

int sigaction(int sig,struct sigaction * sa, struct sigaction * old)
{
	if (sa->sa_flags & SA_NOMASK)
		sa->sa_restorer=___sig_restore;
	else
		sa->sa_restorer=___masksig_restore;
#ifdef PRE_GCC_2
	__asm__("movl %0,%%ebx" : : "g" (sig) : "bx");
	__asm__("movl %0,%%ecx" : : "g" (sa));
	__asm__("movl %0,%%edx" : : "g" (old));
	__asm__("int $0x80" :"=a" (sig) :"0" (__NR_sigaction));
#else
	__asm__("int $0x80":"=a" (sig)
		:"0" (__NR_sigaction),"b" (sig),"c" (sa),"d" (old));
#endif
	if (sig>=0)
		return sig;
	errno = -sig;
	return -1;
}
