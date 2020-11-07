#pragma once
#include "stdafx.h"
#include <math.h>

class Item
{
public:
  Item(QString addNom, double addStock, double addPrixAchat, double addPrixVente, int addPoid, QString addPix, double addAveSell, int addId);
  Item(QString addNom, double addStock, double addPrixVente, int addId);

  QString getNom();
  double getStock();
  int getRoundedStock();
  double getBuyP();
  double getSellP();
  int getPoid();
  QString getPix();
  double getAveSell();

  int getId();
  void setStock(double newStock);

private:
  QString nom;
  double stock;
  double prixAchat;
  double prixVente;
  int poid;
  QString pix;
  double aveSell;
  int id;
};
