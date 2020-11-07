#include "Factory.h"

Factory::Factory()
{
  level = 1;
  dailyProduction = 1;
  productionCost = 0;
  randProd = 1;
  nextUpgrade = 500 + Static::randZeroToVal(500);
  evolution = true;
}

void Factory::newMonthFactory(int days)
{
  calculEvolution();
  expodentialProduction(days);
  productionCost = dailyProduction * 3.0;
  productionCost += Static::randNegativeIntToPercentage(5);
}

void Factory::expodentialProduction(int days)
{
  dailyProduction = 1;
  for (int i = 0; i < level; i++)
  {
    dailyProduction *= 1.5;
  }
  dailyProduction *= randProd;
  dailyProduction *= days;
}

void Factory::calculEvolution()
{
  int dice = Static::randZeroToVal(100);
  if (dice > 80)
  {
    if (evolution)
    {
      evolution = false;
    }
    else
    {
      evolution = true;
    }
  }
  if (evolution)
  {
    randProd += Static::randOnlyPositivePercentage(5);
  }
  else
  {
    randProd -= Static::randOnlyPositivePercentage(5);
  }
}

void Factory::upgradeAccepted()
{
  level++;
  nextUpgrade *= (2 + Static::randOnlyPositivePercentage(50));
}

int Factory::getLevel()
{
  return level;
}

double Factory::getProduction()
{
  return dailyProduction;
}

double Factory::getCost()
{
  return productionCost;
}

int Factory::getNextUpgrade()
{
  return nextUpgrade;
}
