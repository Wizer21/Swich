#include "Item.h"

Item::Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  poid = addPoid;
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
