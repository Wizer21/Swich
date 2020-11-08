#include "City.h"

City::City(QString addNom, double addPopularity, std::vector<Item> addCityItemList)
{
  nom = addNom;
  popularity = addPopularity;
  cityItemList = addCityItemList;
}

QString City::getNom()
{
  return nom;
}

std::vector<Item> City::getList()
{
  return cityItemList;
}

void City::addToList(Item item)
{
  for (int i = 0; i < cityItemList.size(); i++)
  {
    if (cityItemList.at(i).getId() == item.getId())
    {
      cityItemList.at(i).setStock(cityItemList.at(i).getStock() + item.getStock());
      return;
    }
  }
  Item newItem(item.getNom(), item.getStock(), item.getSellP(), item.getId());
  cityItemList.push_back(newItem);
}

void City::removeStock(int id, int vol)
{
  for (int i = 0; i < cityItemList.size(); i++)
  {
    if (cityItemList.at(i).getId() == id)
    {
      cityItemList.at(i).setStock(cityItemList.at(i).getStock() - vol);
      eraseIfEmpty();
      return;
    }
  }
}

void City::eraseIfEmpty()
{
  for (int i = 0; i < cityItemList.size(); i++)
  {
    if (cityItemList.at(i).getStock() == 0)
    {
      cityItemList.erase(cityItemList.begin() + i);
      i--;
    }
  }
}

QString City::randSells(double valAd)
{
  int sold = 1 + Static::randZeroToVal(5);
  double newBank = 0;
  int newVolSold = 0;
  int SoldQuantity;
  int stockCurrentItem;
  for (int i = 0; i < cityItemList.size(); i++)
  {
    stockCurrentItem = cityItemList.at(i).getStock();
    if (stockCurrentItem != 0)
    {
      SoldQuantity = sold * valAd;

      if (stockCurrentItem - SoldQuantity < 0)
      {
        SoldQuantity += (stockCurrentItem - SoldQuantity);
      }
      newBank += cityItemList.at(i).getSellP() * SoldQuantity;
      newVolSold += SoldQuantity;

      cityItemList.at(i).setStock(stockCurrentItem - SoldQuantity);
    }
  }
  return QString("%1$%2").arg(newBank).arg(newVolSold);
}