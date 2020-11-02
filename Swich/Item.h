#pragma once
#include "stdafx.h"

class Item
{
public:
  Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid);

private:
  QString nom;
  int stock;
  double prixAchat;
  double prixVente;
  int poid;
};
