#include <math.h>

double frexp(double x, int *i)
{
  double rv = x;
  int sign=1;
  int ri = 0;
  if (rv < 0)
  {
    sign = -1;
    rv = -rv;
  }
  while (rv > 1)
  {
    ri++;
    rv /= 2.0;
  }
  while (rv < 0.5)
  {
    ri--;
    rv *= 2;
  }
  *i = ri;
  return rv*sign;
}

