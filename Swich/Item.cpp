#include "Item.h"

Item::Item(QString addNom, double addStock, double addPrixAchat, double addPrixVente, QString addPix, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  pix = addPix;
  id = addId;
}

Item::Item(QString addNom, double addStock, double addPrixVente, int addId)
{
  nom = addNom;
  stock = addStock;
  prixAchat = 0;
  prixVente = addPrixVente;
  pix = "";
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