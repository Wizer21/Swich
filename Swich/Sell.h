#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"
#include "City.h"

class Sell : public QWidget
{
  Q_OBJECT

public:
  Sell(std::vector<Item>& item, std::vector<City>& city);

private slots:
  void dynamicStock(int);

private:
  int id;
  void setSell();
  void setList(QVBoxLayout*);
  void setCity(QTabWidget*);
  std::vector<Item>* getItemList;
  std::vector<City>* getCityList;
};
