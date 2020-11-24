#pragma once
#include <qwidget.h>
#include <math.h>
#include "stdafx.h"
#include "Factory.h"
#include "Utils.h"
#include "SingleData.h"
#include "ItemDAO.h"

class Production : public QWidget
{
  Q_OBJECT

public:
  Production();
  QString newMonthProd(int days);
  void validatedUpgrade(int id);
  void validateNewFactory(int id);
  void loadDB();
  void saveToDB();

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

  std::vector<std::pair<int, int>> factoryLevel_upgrade;

  void setProduction();
  QWidget* newFactoryWidget(QString getName, int idList);
  void updateWidgets();

  QLabel* displayProduction;
  QGridLayout* layoutProduction;
  QPushButton* lockedFactory1;
  QPushButton* lockedFactory2;
  QVBoxLayout* layout1;
  QVBoxLayout* layout2;

  std::vector<QWidget*> hidedWidget;
  std::vector<std::pair<QLabel*, QPushButton*>> listLvl_Upgrade;

  std::vector<Factory> listFactory;
  std::vector<QLabel*> productionlist;

  std::vector<QLabel*> levelList;
  std::vector<QPushButton*> upgradeList;
};
