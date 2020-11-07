#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Item.h"

class Stock : public QWidget
{
public:
  Stock(std::vector<Item>& getItemList);
  void setList();

private:
  void setStock();
  QTableWidget* tab;
  std::vector<Item>* listItem;
};
