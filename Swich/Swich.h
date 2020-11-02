#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Swich.h"
#include "stdafx.h"
#include "Analytics.h"
#include "Hub.h"
#include "Item.h"
#include "Ad.h"
#include "Sell.h"

class Swich : public QMainWindow
{
  Q_OBJECT

public:
  Swich(QWidget* parent = Q_NULLPTR);

private slots:
  void connectToHub();
  void connectToAnalytics();
  void connectToSell();
  void connectToAd();

private:
  void ini(QGridLayout* widget);
  void createDefaultWidget();
  void setDefaultItem();

  int day;
  // TEMPORAIRE ------------
  double a;
  double b;
  double c;

  QStackedWidget* swichZoneWidget;
  Hub* widgetHub;
  Analytics* widgetAnalytics;
  Sell* widgetSell;
  Ad* widgetAd;

  std::vector<Item> itemList;

  Ui::SwichClass ui;
};
