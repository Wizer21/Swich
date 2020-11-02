#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Swich.h"
#include "stdafx.h"
#include "Analytics.h"
#include "Hub.h"
#include "Item.h"
#include "Ad.h"

class Swich : public QMainWindow
{
  Q_OBJECT

public:
  Swich(QWidget* parent = Q_NULLPTR);

public slots:
  void connectToHub();
  void connectToAnalytics();
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
  Ad* widgetAd;

  std::vector<Item> itemList;

  Ui::SwichClass ui;
};
