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
#include "Utils.h"
#include "Options.h"
#include "Credits.h"
#include <math.h>
#include "DragEmployee.h"
#include "ItemDAO.h"
#include "Database.h"
#include <cmath>
#include "Tutorial.h"

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
  void openDatabase();
  void openTutorial();
  void applyNewCommercial(DragEmployee* getActualEmployee);
  void applyFireCommercial();
  void applyCommercialIsActivated(bool);
  void applyTableChanged();
  void buttonSaveToDatabase();
  void applyTutorialMooved(QPoint);

protected:
  void Swich::moveEvent(QMoveEvent* event);
  void Swich::resizeEvent(QResizeEvent* event);

private:
  void ini(QGridLayout* widget);
  void createDefaultWidget();
  void setDefaultList();
  std::pair<double, int> addProductionToInventory(double production);
  void setTheme();
  void commercialTransfertStock();
  void updateNotificationChat(bool isVisible);
  QString randSells(double valAd);

  double bankDisplayed;
  bool gotCommercial;
  bool commercialActivated;
  bool positiveBank;

  QStackedWidget* swichZoneWidget;
  Hub* widgetHub;
  Analytics* widgetAnalytics;
  Sell* widgetSell;
  Production* widgetProduction;
  Ad* widgetAd;
  Stock* widgetStock;
  Chat* widgetChat;
  QPushButton* saveButton;

  QMenuBar* bar;
  QMenu* more;
  QLabel* sold;
  QLabel* actualDb;

  std::vector<Item>* mainItemList;
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
