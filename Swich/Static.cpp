#include "Static.h"

int Static::randZeroToVal(const int& val)
{
  //std::default_random_engine generator;
  //std::uniform_int_distribution<int> randVal(0, val);
  //int finalVal = randVal(generator);
  //return finalVal;

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