#include "Item.h"

Item::Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid)
{
  nom = addNom;
  stock = addStock;
  prixAchat = addPrixAchat;
  prixVente = addPrixVente;
  poid = addPoid;
}
