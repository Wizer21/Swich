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
#include "Static.h"
#include "Options.h"
#include "Credits.h"
#include <math.h>

class Swich : public QMainWindow
{
  Q_OBJECT

public:
  Swich(QWidget* parent = Q_NULLPTR);

private slots:
  void connectToMenu();
  void startNewMonth();
  void applyUpdateStock();
  void applyUpgradeFactory(int cost, int id);
  void applyNewFactory(int cost, int id);
  void openOptions();
  void openCredits();

private:
  void ini(QGridLayout* widget);
  void createDefaultWidget();
  void setDefaultList();
  double addProductionToInventory(double production);

  int turnId;
  double bankDisplayed;

  QStackedWidget* swichZoneWidget;
  Hub* widgetHub;
  Analytics* widgetAnalytics;
  Sell* widgetSell;
  Production* widgetProduction;
  Ad* widgetAd;
  Stock* widgetStock;
  Chat* widgetChat;

  QLineEdit* sold;

  std::vector<double> historyBank;
  std::vector<double> moneyMovements;
  std::vector<int> historySoldVol;
  std::vector<Item> itemList;
  std::vector<City> cityList;
  std::vector<Contact> contactList;

  QPushButton* hub;
  QPushButton* analytics;
  QPushButton* sell;
  QPushButton* production;
  QPushButton* pub;
  QPushButton* stock;
  QPushButton* chat;

  Ui::SwichClass ui;
};
