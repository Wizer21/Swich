#include "Static.h"

double Static::randZeroToVal(int val)
{
  return rand() % val;
}

double Static::randNegativeIntToPercentage(int val)
{
  int positive = rand() % val;
  int negative = (rand() % val) * 2;
  return val * 0.01;
}

double Static::randOnlyPositivePercentage(int val)
{
  return rand() % val * 0.01;
}