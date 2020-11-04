#pragma once
#include "stdafx.h"

class Item
{
public:
  Item(QString addNom, int addStock, double addPrixAchat, double addPrixVente, int addPoid, QString addPix, double addAveSell, int addId);
  Item(QString addNom, int addStock, double addPrixVente);
  QString getNom();
  int getStock();
  double getBuyP();
  double getSellP();
  int getPoid();
  QString getPix();
  double getAveSell();
  int getId();
  void setStock(int newStock);

private:
  QString nom;
  int stock;
  double prixAchat;
  double prixVente;
  int poid;
  QString pix;
  double aveSell;
  int id;
};
