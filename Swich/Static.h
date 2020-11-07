#pragma once
#include "qrandom.h"

class Static
{
public:
  static double randZeroToVal(int val);
  static double randNegativeIntToPercentage(int val);
  static double randOnlyPositivePercentage(int val);
};
