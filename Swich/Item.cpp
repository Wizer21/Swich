#include "Item.h"

Item::Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid, QString addPix, double addAveSell)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  poid = addPoid;
  pix = addPix;
  aveSell = addAveSell;
}

Item::Item(QString addNom, int addStock, double addPrixVente)
{
  nom = addNom;
  stock = addStock;
  prixVente = addPrixVente;
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
