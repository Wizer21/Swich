#include "Factory.h"

Factory::Factory()
{
  level = 0;
  dailyProduction = 0;
  productionCost = 0;
  randProd = 0;
  nextUpgrade = 0;
  evolution = true;
}

Factory::Factory(int addLevel, double addDailyProduction, double addDailyCost, double addRandProd, int addNextUpgrade)
{
  level = addLevel;
  dailyProduction = addDailyProduction;
  productionCost = addDailyCost;
  randProd = addRandProd;
  nextUpgrade = addNextUpgrade;
  evolution = true;
}

Factory Factory::setUpNewOne()
{
  double newProd = 100 + Static::randNegativeIntToPercentage(10);
  double newCost = newProd * 2;
  return Factory(1, newProd, newCost * Static::randNegativeIntToPercentage(10), 1, 1000);
}

void Factory::newMonthFactory(int days)
{
  calculEvolution();
  expodentialProduction(days);
  productionCost = dailyProduction * 3;
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
