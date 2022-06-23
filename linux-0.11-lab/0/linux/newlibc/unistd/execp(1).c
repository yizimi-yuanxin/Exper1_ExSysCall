#define __LIBRARY__
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

extern char ** environ;

static char tmp_path[PATH_MAX+1];

static inline _syscall3(int,execve,const char *,file,char **,argv,char **,envp)

static int execvep(const char * file, char ** argv, char ** envp)
{
	char * path, * tmp;
	int len;
	struct stat st;

	if (*file=='/' || !*file || !(path=getenv("PATH")))
		return execve(file,argv,envp);
	while (*path) {
		tmp=tmp_path;
		len=0;
		while (len<PATH_MAX && *path && *path!=':') {
			*(tmp++) = *(path++);
			len++;
		}
		if (*path==':')
			path++;
		if (!len || tmp[-1]!='/') {
			*(tmp++) = '/';
			len++;
		}
		if (len>=PATH_MAX)
			continue;
		strncpy(tmp,file,PATH_MAX-len);
		if (stat(tmp_path,&st))
			continue;
		else
			if (!(st.st_mode & S_IFREG))
				continue;
		if (!access(tmp_path,1))
			return execve(tmp_path,argv,envp);
	}
	errno = ENOEXEC;
	return -1;
}

int execvp(const char * file, char ** argv)
{
	return execvep(file,argv,environ);
}

int execlp(const char * file, char * arg0, ...)
{
	return execvep(file,&arg0,environ);
}
