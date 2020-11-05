#include "Item.h"

Item::Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid, QString addPix, double addAveSell, int addId)
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

Item::Item(QString addNom, int addStock, double addPrixVente, int addId)
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

int Item::getStock()
{
  return stock;
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

void Item::setStock(int newStock)
{
  stock = newStock;
}