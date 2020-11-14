#include "Static.h"

double Static::randZeroToVal(const int& val)
{
  return rand() % val;
}

double Static::randNegativeIntToPercentage(const int& val)
{
  return (randZeroToVal(val) - randZeroToVal(val) * 2) * 0.01;
}

double Static::randOnlyPositivePercentage(const int& val)
{
  return rand() % val * 0.01;
}