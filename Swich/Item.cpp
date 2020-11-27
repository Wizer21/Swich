#include "Item.h"

Item::Item()
{
  nom = "";
  stock = 0;
  prixAchat = 0;
  prixVente = 0;
  pix = "";
  id = 0;
  factoryStrength = 0;
  employeeStrength = 0;
  commercialStrenght = 0;
}

Item::Item(QString addNom, double addStock, double addPrixAchat, double addPrixVente, QString addPix, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  pix = addPix;
  id = addId;
  factoryStrength = 0;
  employeeStrength = 0;
  commercialStrenght = 0;
}

Item::Item(QString addNom, double addStock, double addPrixVente, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = 0;
  prixVente = addPrixVente;
  pix = "";
  id = addId;
  factoryStrength = 0;
  employeeStrength = 0;
  commercialStrenght = 0;
}

QString Item::getNom()
{
  return nom;
}

double Item::getStock()
{
  return stock;
}

int Item::getRoundedStock()
{
  return round(stock);
}

double Item::getBuyP()
{
  return prixAchat;
}

double Item::getSellP()
{
  return prixVente;
}

QString Item::getPix()
{
  return pix;
}

int Item::getId()
{
  return id;
}

void Item::setStock(double newStock)
{
  stock = newStock;
}

int Item::pushProduction(double newStrenght)
{
  factoryStrength += newStrenght;
  int itemProducted = 0;
  while (factoryStrength > prixVente / 10)
  {
    factoryStrength -= prixVente / 10;
    itemProducted++;
  }
  stock += itemProducted;
  return itemProducted;
}

int Item::pushSales(double newStrenght)
{
  employeeStrength += newStrenght;
  int itemSold = 0;
  while (employeeStrength > prixVente / 15)
  {
    if (stock <= 0)
    {
      break;
    }
    employeeStrength -= prixVente / 15;
    itemSold++;
    stock--;
  }
  return itemSold;
}

int Item::pushCommercial(int wantedItems)
{
  employeeStrength += wantedItems;
  int itemSold = 0;
  while (employeeStrength > prixVente)
  {
    if (stock <= 0)
    {
      break;
    }
    employeeStrength -= prixVente;
    itemSold++;
    stock--;
  }
  return itemSold;
}