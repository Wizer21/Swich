#include "Item.h"

Item::Item(QString addNom, double addStock, double addPrixAchat, double addPrixVente, int addPoid, QString addPix, double addAveSell, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  poid = addPoid;
  pix = addPix;
  aveSell = addAveSell;
  id = addId;
}

Item::Item(QString addNom, double addStock, double addPrixVente, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = 0;
  prixVente = addPrixVente;
  poid = 0;
  pix = "";
  aveSell = 0;
  id = addId;
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

int Item::getPoid()
{
  return poid;
}

QString Item::getPix()
{
  return pix;
}

double Item::getAveSell()
{
  return aveSell;
}

int Item::getId()
{
  return id;
}

void Item::setStock(double newStock)
{
  stock = newStock;
}