#include <stdlib.h>

/* we're useing GGUBS - should work, but it isn't the best algorithm */

static unsigned long _seed;

int rand(void)
{
	if (!_seed)
		_seed++;
	_seed *= 16807;
	_seed %= 0x7fffffff;
	return _seed-1;
}

void srand(unsigned int seed)
{
	_seed = seed;
}
