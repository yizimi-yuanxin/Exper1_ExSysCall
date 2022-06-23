#define __LIBRARY__
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

extern char ** environ;

static inline _syscall3(int,execve,const char *,file,char **,argv,char **,envp)

int execv(const char * pathname, char ** argv)
{
	return execve(pathname,argv,environ);
}

int execl(const char * pathname, char * arg0, ...)
{
	return execve(pathname,&arg0,environ);
}

int execle(const char * pathname, char * arg0, ...)
{
	char ** env = &arg0;

	while (!*(env++)) ;
	return execve(pathname,&arg0,env);
}
