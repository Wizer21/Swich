#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"
#include "City.h"
#include "Dragwidget.h"
#include "DropWidget.h"
#include "Stock.h"
#include "ItemDAO.h"

class Sell : public QWidget
{
  Q_OBJECT

public:
  Sell(std::vector<City>& city, std::vector<Item>* getListItem);
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
  void setSell();
  void setCity(QTabWidget*);
  void setTabCity(QTableWidget*, std::vector<Item>);
  void updateCityOnDrop(QString vol, int idItem);
  QTabWidget* tabWidget;
  Stock* getStock;
  QWidget* widArea;
  QVBoxLayout* layoutArea;

  std::map<int, QSlider*> sliderList;
  std::vector<Item>* getList;
  std::list<Dragwidget*> widgetFromItemList;
  std::vector<City>* getCityList;
  std::vector<QWidget*> widgetToDelete;
};
