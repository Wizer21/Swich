#pragma once
#include "stdafx.h"
#include "Utils.h"

class Factory
{
public:
  Factory();
  void newMonthFactory(int days);
  void upgradeAccepted();

  int getLevel();
  double getStrenght();
  double getCost();
  int getNextUpgrade();
  void setLevel(int newLevel);
  void setUpgrade(int newUpgrade);

private:
  int level;
  double strenghtProducted;
  double productionCost;
  double randProd;
  int nextUpgrade;
  bool evolution;

  void expodentialProduction(int days);
  void calculEvolution();
};
