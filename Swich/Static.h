#pragma once
#include <random>
#include "stdafx.h"

class Static : public QObject
{
  Q_OBJECT

public:
  static int randZeroToVal(const int& val);
  static double randNegativeIntToPercentage(const int& val);
  static double randOnlyPositivePercentage(const int& val);

private:
  explicit inline Static(){};
  inline ~Static(){};
};
