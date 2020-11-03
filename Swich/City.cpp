#include "City.h"

City::City(QString addNom, double addPopularity)
{
  nom = addNom;
  popularity = addPopularity;
}

QString City::getNom()
{
  return nom;
}

std::vector<Item> City::getList()
{
  return cityItemList;
}