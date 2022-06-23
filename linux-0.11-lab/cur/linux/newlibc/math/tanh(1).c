#include <math.h>

double tanh(double x)
{
  return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

