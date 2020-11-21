#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"
#include "City.h"
#include "Dragwidget.h"
#include "DropWidget.h"
#include "Stock.h"
#include "Jumpslider.h"
#include "ItemDAO.h"

class Sell : public QWidget
{
  Q_OBJECT

public:
  Sell(std::vector<City>& city);
  void refreshStock();
  void setList();

signals:
  void callUpdateStock();

private slots:
  void dynamicStockSender(int vol);
  void dynamicStockId(int id);
  void setNewItem(QString nom, QString vol, int id);
  void cancelSell();
  void validate();

private:
  int id;
  void setSell();
  void setCity(QTabWidget*);
  void setTabCity(QTableWidget*, std::vector<Item>);
  void updateCityOnDrop(QString vol, int idItem);
  QTabWidget* tabWidget;
  Stock* getStock;
  QWidget* widArea;
  QVBoxLayout* layoutArea;
  std::list<Dragwidget*> widgetFromItemList;
  std::vector<City>* getCityList;
  std::vector<QWidget*> widgetToDelete;
};
