#include "Factory.h"

Factory::Factory()
{
  level = 1;
  dailyProduction = 1;
  productionCost = 0;
  randProd = 1;
  nextUpgrade = 500 + Utils::randZeroToVal(500);
  evolution = true;
}

void Factory::newMonthFactory(int days)
{
  calculEvolution();
  expodentialProduction(days);
}

void Factory::expodentialProduction(int days)
{
  dailyProduction = 1;
  productionCost = 100;
  for (int i = 0; i < level; i++)
  {
    dailyProduction *= 1.3;
    productionCost *= 1.2;
  }
  dailyProduction *= randProd;
  dailyProduction *= days;
}

void Factory::calculEvolution()
{
  int dice = Utils::randZeroToVal(100);
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
    randProd += Utils::randOnlyPositivePercentage(5);
  }
  else
  {
    randProd -= Utils::randOnlyPositivePercentage(5);
  }
}

void Factory::upgradeAccepted()
{
  level++;
  nextUpgrade *= (2 + Utils::randOnlyPositivePercentage(50));
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

void Factory::setLevel(int newLevel)
{
  level = newLevel;
}

void Factory::setUpgrade(int newUpgrade)
{
  nextUpgrade = newUpgrade;
}