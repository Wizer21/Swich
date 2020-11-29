#include "Factory.h"

Factory::Factory()
{
  level = 0;
  strenghtProducted = 0;
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
  strenghtProducted = 1;
  productionCost = 30;
  for (int i = 0; i < level; i++)
  {
    strenghtProducted *= 1.4;
    productionCost *= 1.2;
  }
  strenghtProducted *= randProd;
  strenghtProducted *= days;
}

void Factory::calculEvolution()
{
  int dice = Utils::randZeroToVal(100);

  if (randProd > 1 && evolution)
  {
    dice += 10;
  }
  if (randProd < 1 && !evolution)
  {
    dice += 10;
  }

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

double Factory::getStrenght()
{
  return strenghtProducted;
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