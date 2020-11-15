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
#include "DragEmployee.h"

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
  void applyNewCommercial(DragEmployee* getActualEmployee);
  void applyFireCommercial();
  void applyCommercialIsActivated(bool);

private:
  void ini(QGridLayout* widget);
  void createDefaultWidget();
  void setDefaultList();
  double addProductionToInventory(double production);
  void setTheme();
  void commercialTransfertStock();

  int turnId;
  double bankDisplayed;
  bool gotCommercial;
  bool commercialActivated;

  QStackedWidget* swichZoneWidget;
  Hub* widgetHub;
  Analytics* widgetAnalytics;
  Sell* widgetSell;
  Production* widgetProduction;
  Ad* widgetAd;
  Stock* widgetStock;
  Chat* widgetChat;

  QMenuBar* bar;
  QAction* options;
  QAction* credits;
  QLabel* sold;

  std::vector<Item> itemList;
  std::vector<City> cityList;
  std::vector<Contact> contactList;
  DragEmployee* getCommercial;

  QPushButton* hub;
  QPushButton* analytics;
  QPushButton* sell;
  QPushButton* production;
  QPushButton* pub;
  QPushButton* stock;
  QPushButton* chat;

  Ui::SwichClass ui;
};
