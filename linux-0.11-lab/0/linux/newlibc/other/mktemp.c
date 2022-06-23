#include <unistd.h>
#include <string.h>

char * mktemp(char * template)
{
	int pid;
	int len;

	pid = getpid();
	len = strlen(template);
	while (len-->0 && template[len] == 'X') {
		template[len] = '0' + (pid % 10);
		pid = pid / 10;
	}
	return(template);
}
