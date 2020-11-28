#pragma once
#include "stdafx.h"
#include "Item.h"
#include "Utils.h"

class City
{
public:
  City::City(QString addNom, double addPopularity, std::vector<Item>* addCityItemList);
  QString getNom();
  std::vector<Item>* getList();
  void setList(std::vector<Item>* list);
  void addToList(Item);
  void removeStock(int id, int vol);
  void pushStockToList(int idCurrentItem, double addedStock);

private:
  QString nom;
  double popularity;
  std::vector<Item>* cityItemList;
};
