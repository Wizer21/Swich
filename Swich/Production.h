#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Factory.h"

class Production : public QWidget
{
public:
  Production();
  QString newMonthProd(int days);

private:
  void setProduction();
  QWidget* newFactoryWidget();
  void updateWidgets();

  Factory factoryFunctions;
  std::vector<Factory> listFactory;
  std::vector<QLabel*> levelList;
  std::vector<QLabel*> productionlist;
  std::vector<QPushButton*> upgradeList;
};
