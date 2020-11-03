#pragma once
#include "stdafx.h"

class Item
{
public:
  Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid);
  Item(QString addNom, int addStock, double addPrixVente);
  QString getNom();
  int getStock();

private:
  QString nom;
  int stock;
  double prixAchat;
  double prixVente;
  int poid;
};
