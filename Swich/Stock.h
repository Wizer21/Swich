#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"
#include "DragEmployee.h"
#include "SingleData.h"

class Stock : public QWidget
{
  Q_OBJECT

public:
  Stock(std::vector<Item>& getItemList);
  void setList();
  void updateStock();
  void updateCommercialSlot(DragEmployee* getEmploye);
  void firedCommercial();
  void setItemPushed(int nrbItem);

public slots:
  void updateRadioButton(int);

signals:
  void setIsActivated(bool isActivated);

private:
  void setStock();
  QTableWidget* tab;
  std::vector<Item>* listItem;
  QHeaderView* head;

  QWidget* commercialWidget;
  QLabel* pictureId;
  QLabel* name;
  QLabel* salary;
  QLabel* displayPushedItems;
  QLabel* textDefault;
};
