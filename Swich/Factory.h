#pragma once
#include "stdafx.h"
#include "Static.h"

class Factory
{
public:
  Factory();
  Factory(int addLevel, double addDailyProduction, double addDailyCost, double addRandProd, int addNextUpgrade);
  Factory setUpNewOne();
  void newMonthFactory(int days);

  int getLevel();
  double getProduction();
  double getCost();
  int getNextUpgrade();

private:
  int level;
  double dailyProduction;
  double productionCost;
  double randProd;
  int nextUpgrade;
  bool evolution;

  void expodentialProduction(int days);
  void calculEvolution();
};
