#include "Static.h"

double Static::randZeroToVal(int val)
{
  return rand() % val;
}

double Static::randNegativeIntToPercentage(int val)
{
  return (rand() % val - (rand() % val) * 2) * 0.01;
}