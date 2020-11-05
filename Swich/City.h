#pragma once
#include "stdafx.h"
#include "Item.h"

class City
{
public:
  City::City(QString addNom, double addPopularity, std::vector<Item> addCityItemList);
  QString getNom();
  std::vector<Item> getList();
  void addToList(Item);
  void removeStock(int id, int vol);
  void eraseIfEmpty();

private:
  QString nom;
  double popularity;
  std::vector<Item> cityItemList;
};
