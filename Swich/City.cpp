#include "City.h"

City::City(QString addNom, double addPopularity, std::vector<Item>* addCityItemList)
{
  nom = addNom;
  popularity = addPopularity;
  cityItemList = addCityItemList;
}

QString City::getNom()
{
  return nom;
}

std::vector<Item>* City::getList()
{
  return cityItemList;
}

void City::setList(std::vector<Item>* list)
{
  cityItemList = list;
}

void City::addToList(Item item)
{
  for (int i = 0; i < cityItemList->size(); i++)
  {
    if (cityItemList->at(i).getId() == item.getId())
    {
      cityItemList->at(i).setStock(cityItemList->at(i).getStock() + item.getStock());
      return;
    }
  }
  Item newItem(item.getNom(), item.getStock(), item.getSellP(), item.getId());
  cityItemList->push_back(newItem);
}

void City::removeStock(int id, int vol)
{
  int sizeList = (int)cityItemList->size();
  for (int i = 0; i < sizeList; i++)
  {
    if (cityItemList->at(i).getId() == id)
    {
      cityItemList->at(i).setStock(cityItemList->at(i).getStock() - vol);
      //eraseIfEmpty();
      return;
    }
  }
}

void City::eraseIfEmpty()
{
  for (int i = 0; i < cityItemList->size(); i++)
  {
    if (cityItemList->at(i).getStock() == 0)
    {
      cityItemList->erase(cityItemList->begin() + i);
      i--;
    }
  }
}

void City::pushStockToList(int idCurrentItem, double addedStock)
{
  int sizeList = (int)cityItemList->size();
  for (int i = 0; i < sizeList; i++)
  {
    if (cityItemList->at(i).getId() == idCurrentItem)
    {
      cityItemList->at(i).setStock(cityItemList->at(i).getStock() + addedStock);
      return;
    }
  }
}