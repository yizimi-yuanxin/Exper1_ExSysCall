#include <stdlib.h>
#include <string.h>

/*
 * Simple getenv. Linus
 */

extern char ** environ;

char * getenv(const char * name)
{
	int len;
	char * tmp;
	char ** env;

	len = strlen(name);
	if (env=environ)
		while (tmp=*(env++)) {
			if (strncmp(name,tmp,len))
				continue;
			if (tmp[len]=='=')
				return tmp+len+1;
		}
	return NULL;
}
