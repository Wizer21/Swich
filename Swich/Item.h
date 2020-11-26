#pragma once
#include "stdafx.h"
#include <math.h>

class Item
{
public:
  Item();
  Item(QString addNom, double addStock, double addPrixAchat, double addPrixVente, QString addPix, int addId);
  Item(QString addNom, double addStock, double addPrixVente, int addId);

  QString getNom();
  double getStock();
  int getRoundedStock();
  double getBuyP();
  double getSellP();
  QString getPix();
  int pushProduction(double newStrenght);
  int pushSales(double newStrenght);

  int getId();
  void setStock(double newStock);

private:
  QString nom;
  double stock;
  double prixAchat;
  double prixVente;
  QString pix;
  int id;
  double factoryStrength;
  double employeeStrength;
};
