#pragma once
#include "stdafx.h"
#include "Static.h"

class Factory
{
public:
  Factory();
  void newMonthFactory(int days);
  void upgradeAccepted();

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
