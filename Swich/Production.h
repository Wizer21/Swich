#pragma once
#include <qwidget.h>
#include <math.h>
#include "stdafx.h"
#include "Factory.h"
#include "Static.h"
#include "SingleData.h"

class Production : public QWidget
{
  Q_OBJECT

public:
  Production();
  QString newMonthProd(int days);
  void validatedUpgrade(int id);
  void validateNewFactory(int id);

signals:
  void transfertUpgrade(int, int);
  void transfertNewFactory(int cost, int id);

private slots:
  void upgradeFactory();
  void askNewFactory();

private:
  int idButton;
  int lockedPrice1;
  int lockedPrice2;

  void setProduction();
  QWidget* newFactoryWidget(QString getName, QString objName);
  void updateWidgets();

  QLabel* displayProduction;
  QGridLayout* layoutProduction;
  QPushButton* lockedFactory1;
  QPushButton* lockedFactory2;
  QVBoxLayout* layout1;
  QVBoxLayout* layout2;

  std::vector<Factory> listFactory;
  std::vector<QLabel*> levelList;
  std::vector<QLabel*> productionlist;
  std::vector<QPushButton*> upgradeList;
};
