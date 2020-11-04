#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Swich.h"
#include "stdafx.h"
#include "Analytics.h"
#include "Hub.h"
#include "Item.h"
#include "Ad.h"
#include "Sell.h"
#include "City.h"
#include "Production.h"
#include "Stock.h"
#include "Chat.h"
#include "Contact.h"

class Swich : public QMainWindow
{
  Q_OBJECT

public:
  Swich(QWidget* parent = Q_NULLPTR);

private slots:
  void connectToMenu();

private:
  void ini(QGridLayout* widget);
  void createDefaultWidget();
  void setDefaultList();

  int day;
  int id;
  double bank;
  // TEMPORAIRE ------------
  double a;
  double b;
  double c;

  QStackedWidget* swichZoneWidget;
  Hub* widgetHub;
  Analytics* widgetAnalytics;
  Sell* widgetSell;
  Production* widgetProduction;
  Ad* widgetAd;
  Stock* widgetStock;
  Chat* widgetChat;

  std::vector<Item> itemList;
  std::vector<City> cityList;
  std::vector<Contact> contactList;

  Ui::SwichClass ui;
};
