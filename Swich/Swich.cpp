#include "Swich.h"
#include "stdafx.h"

Swich::Swich(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  turnId = 0;
  id = 0;
  bankDisplayed = 1156;

  setDefaultList();
  createDefaultWidget();
  QGridLayout* swichLayout = new QGridLayout(this->ui.centralWidget);
  ini(swichLayout);
}

void Swich::ini(QGridLayout* layout)
{
  //Menu Bar
  QMenuBar* bar = new QMenuBar(this);
  QAction* options = new QAction(tr("Options"));
  QAction* credits = new QAction(tr("Credits"));

  this->setMenuBar(bar);
  bar->addAction(options);
  bar->addAction(credits);

  // Left Band
  QWidget* widgetMenu = new QWidget(this);
  QVBoxLayout* layoutMenu = new QVBoxLayout(this);
  QLabel* swich = new QLabel(tr("Swich"), this);
  QPushButton* hub = new QPushButton(tr("Hub"), this);
  QPushButton* analytics = new QPushButton(tr("Analytics"), this);
  QPushButton* sell = new QPushButton(tr("Sell"), this);
  QPushButton* production = new QPushButton(tr("Production"), this);
  QPushButton* pub = new QPushButton(tr("Ad"), this);
  QPushButton* stock = new QPushButton(tr("Stock"), this);
  QPushButton* chat = new QPushButton(tr("Chat"), this);
  sold = new QLineEdit(QString::number(bankDisplayed), this);

  layout->addWidget(widgetMenu, 0, 0);
  widgetMenu->setLayout(layoutMenu);
  layoutMenu->addWidget(swich);
  layoutMenu->addWidget(hub);
  layoutMenu->addWidget(analytics);
  layoutMenu->addWidget(sell);
  layoutMenu->addWidget(production);
  layoutMenu->addWidget(pub);
  layoutMenu->addWidget(stock);
  layoutMenu->addWidget(chat);
  layoutMenu->addWidget(sold);

  // Right Zone
  swichZoneWidget = new QStackedWidget(this);

  layout->addWidget(swichZoneWidget, 0, 1);

  swichZoneWidget->addWidget(widgetHub);
  swichZoneWidget->addWidget(widgetAnalytics);
  swichZoneWidget->addWidget(widgetSell);
  swichZoneWidget->addWidget(widgetProduction);
  swichZoneWidget->addWidget(widgetAd);
  swichZoneWidget->addWidget(widgetStock);
  swichZoneWidget->addWidget(widgetChat);

  swichZoneWidget->setCurrentIndex(0);

  // Set some options
  hub->setObjectName(QString::number(id++));
  analytics->setObjectName(QString::number(id++));
  sell->setObjectName(QString::number(id++));
  production->setObjectName(QString::number(id++));
  pub->setObjectName(QString::number(id++));
  stock->setObjectName(QString::number(id++));
  chat->setObjectName(QString::number(id++));

  sold->setReadOnly(true);
  sold->setAcceptDrops(false);
  layoutMenu->setAlignment(Qt::AlignTop);
  widgetMenu->setMaximumWidth(this->width() * 0.3);
  widgetMenu->setMinimumWidth(this->width() * 0.3);

  // Connection Menu
  connect(hub, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(analytics, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(sell, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(production, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(pub, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(stock, SIGNAL(clicked()), this, SLOT(connectToMenu()));
  connect(chat, SIGNAL(clicked()), this, SLOT(connectToMenu()));

  connect(widgetHub, SIGNAL(transfertNewMounth()), this, SLOT(startNewMonth()));
  connect(widgetSell, SIGNAL(callUpdateStock()), this, SLOT(applyUpdateStock()));
  connect(widgetProduction, SIGNAL(transfertUpgrade(int, int)), this, SLOT(applyUpgradeFactory(int, int)));
  connect(widgetProduction, SIGNAL(transfertNewFactory(int, int)), this, SLOT(applyNewFactory(int, int)));
}

void Swich::createDefaultWidget()
{
  widgetHub = new Hub();
  widgetAnalytics = new Analytics();
  widgetSell = new Sell(itemList, cityList);
  widgetProduction = new Production();
  widgetAd = new Ad();
  widgetStock = new Stock(itemList);
  widgetChat = new Chat(contactList);
}

void Swich::setDefaultList()
{
  Item item1("Ariane", 10, 10, 20, 100, "", 0, 0);
  Item item2("Hubble", 5, 20, 40, 200, "", 0, 1);
  Item item3("ISS", 0, 30, 50, 300, ":/Swich/iss.png", 0, 2);

  itemList.push_back(item1);
  itemList.push_back(item2);
  itemList.push_back(item3);

  std::vector<Item> listCity1;
  std::vector<Item> listCity2;
  std::vector<Item> listCity3;

  City city1(tr("Paris"), 1, listCity1);
  City city2(tr("Tokyo"), 1, listCity2);
  City city3(tr("London"), 1, listCity3);

  cityList.push_back(city1);
  cityList.push_back(city2);
  cityList.push_back(city3);
  cityList.at(0).addToList(item1);

  Contact contact1("Simon", ":/Swich/simon_id.jpg");
  Contact contact2("Bob", "");

  contactList.push_back(contact1);
  contactList.push_back(contact2);

  for (int i = 0; i < 24; i++)
  {
    historyBank.push_back(1156);
    historySoldVol.push_back(10);
  }
}

void Swich::connectToMenu()
{
  swichZoneWidget->setCurrentIndex(sender()->objectName().toInt());
}

void Swich::applyUpdateStock()
{
  widgetStock->setList();
}

void Swich::startNewMonth()
{
  double temporaryGain = 0;
  double temporarySoldVol = 0;
  double temporaryCharges = 0;
  int addedDays = 30 + Static::randZeroToVal(5);

  for (int i = 0; i < cityList.size(); i++)
  {
    QStringList getValue = (cityList.at(i).randSells()).split("$");
    temporaryGain += getValue.at(0).toInt();
    temporarySoldVol += getValue.at(1).toInt();
  }

  //Update Widgets
  QString prod_Cost = widgetProduction->newMonthProd(addedDays);
  QStringList listProd_Cost = prod_Cost.split("$");
  temporaryCharges += listProd_Cost.at(1).toDouble();

  bankDisplayed += temporaryGain - temporaryCharges;

  sold->setText(QString::number(bankDisplayed));
  QString date = widgetHub->updateCurrentMonth(temporaryGain, temporarySoldVol, addedDays);
  widgetHub->updateAndScrollWidgets(date, QString::number(temporarySoldVol), QString::number(bankDisplayed));

  moneyMovements.insert(moneyMovements.begin(), temporaryGain);
  historyBank.insert(historyBank.begin(), bankDisplayed);
  historySoldVol.insert(historySoldVol.begin(), temporarySoldVol);

  widgetAnalytics->updateAnalytics(turnId++, temporarySoldVol, bankDisplayed, temporaryCharges, listProd_Cost.at(0).toDouble());
  addProductionToInventory(listProd_Cost.at(0).toDouble());
  widgetHub->updateLabels(historyBank, historySoldVol);
  widgetSell->refreshStock();
  widgetStock->setList();
}

void Swich::addProductionToInventory(double production)
{
  int items = itemList.size();
  int nrbIteration = 15 + Static::randZeroToVal(10);
  double prodToPush = production / nrbIteration;

  for (int i = 0; i < nrbIteration; i++)
  {
    int randoItem = Static::randZeroToVal(items);
    itemList.at(randoItem).setStock(itemList.at(randoItem).getStock() + prodToPush);
  }
}

void Swich::applyUpgradeFactory(int cost, int id)
{
  if (cost > bankDisplayed)
  {
    return;
  }
  bankDisplayed -= cost;
  sold->setText(QString::number(bankDisplayed));
  widgetProduction->validatedUpgrade(id);
}

void Swich::applyNewFactory(int cost, int id)
{
  if (cost > bankDisplayed)
  {
    return;
  }
  bankDisplayed -= cost;
  sold->setText(QString::number(bankDisplayed));
  widgetProduction->validateNewFactory(id);
}