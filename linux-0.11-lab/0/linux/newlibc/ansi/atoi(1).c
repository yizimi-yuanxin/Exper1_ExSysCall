#include <stdlib.h>

/*
 * see strtol.c for these. Linus
 */

int atoi(const char *s)
{
	return (int) strtol(s, (char **) NULL, 10);
}

long atol(const char *s)
{
	return strtol(s, (char **) NULL, 10);
}

