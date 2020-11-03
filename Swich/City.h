#pragma once
#include "stdafx.h"
#include "Item.h"

class City
{
public:
  City::City(QString addNom, double addPopularity);
  QString getNom();
  std::vector<Item> getList();

private:
  QString nom;
  double popularity;
  std::vector<Item> cityItemList;
};
