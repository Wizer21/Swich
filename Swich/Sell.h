#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"
#include "City.h"
#include "Dragwidget.h"
#include "DropWidget.h"

class Sell : public QWidget
{
  Q_OBJECT

public:
  Sell(std::vector<Item>& item, std::vector<City>& city);

private slots:
  void dynamicStock(int);
  void setNewItem(QString nom, QString vol, int id);

private:
  int id;
  void setSell();
  void setList(QVBoxLayout*);
  void setCity(QTabWidget*);
  QTabWidget* tabWidget;
  std::vector<Item>* getItemList;
  std::vector<City>* getCityList;
};
