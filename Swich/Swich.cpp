#include "Swich.h"
#include "stdafx.h"

Swich::Swich(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  turnId = 0;
  bankDisplayed = 11560;
  gotCommercial = false;
  commercialActivated = true;
  setDefaultList();
  createDefaultWidget();
  QGridLayout* swichLayout = new QGridLayout(this->ui.centralWidget);
  ini(swichLayout);
}

void Swich::ini(QGridLayout* layout)
{
  //Menu Bar
  bar = new QMenuBar(this);
  options = new QAction(tr("Settings"));
  credits = new QAction(tr("Credits"));

  this->setMenuBar(bar);
  bar->addAction(options);
  bar->addAction(credits);

  // Left Band
  QWidget* widgetMenu = new QWidget(this);
  QVBoxLayout* layoutMenu = new QVBoxLayout(this);
  QLabel* swich = new QLabel(tr("Swich"), this);
  hub = new QPushButton(tr("Hub"), this);
  analytics = new QPushButton(tr("Analytics"), this);
  sell = new QPushButton(tr("Sales"), this);
  production = new QPushButton(tr("Production"), this);
  pub = new QPushButton(tr("Team"), this);
  stock = new QPushButton(tr("Stock"), this);
  chat = new QPushButton(tr("Chat"), this);
  QWidget* containSold = new QWidget(this);
  QHBoxLayout* layoutSold = new QHBoxLayout(this);
  QLabel* logoSol = new QLabel(this);
  sold = new QLabel(QString::number(bankDisplayed), this);

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
  layout->addWidget(containSold, 1, 0);
  containSold->setLayout(layoutSold);
  layoutSold->addWidget(logoSol);
  layoutSold->addWidget(sold);

  // Right Zone
  swichZoneWidget = new QStackedWidget(this);

  layout->addWidget(swichZoneWidget, 0, 1, 2, 1);

  swichZoneWidget->addWidget(widgetHub);
  swichZoneWidget->addWidget(widgetAnalytics);
  swichZoneWidget->addWidget(widgetSell);
  swichZoneWidget->addWidget(widgetProduction);
  swichZoneWidget->addWidget(widgetAd);
  swichZoneWidget->addWidget(widgetStock);
  swichZoneWidget->addWidget(widgetChat);

  //Theme Name
  QFont font(qApp->font());
  swich->setStyleSheet("font-size:40px;" + font.toString() + ";");
  sold->setStyleSheet("font-size:40px;" + font.toString() + ";");

  SingleData* getData = getData->getInstance();
  getData->addLabelToAdaptOnTheme("piece", logoSol);

  hub->setObjectName("index0");
  analytics->setObjectName("index1");
  sell->setObjectName("index2");
  production->setObjectName("index3");
  pub->setObjectName("index4");
  stock->setObjectName("index5");
  chat->setObjectName("index6");

  widgetHub->setObjectName("hub");
  widgetAnalytics->setObjectName("analytics");
  widgetSell->setObjectName("sell");
  widgetProduction->setObjectName("production");
  widgetAd->setObjectName("ad");
  widgetStock->setObjectName("stock");
  widgetChat->setObjectName("chat");

  swichZoneWidget->setCurrentIndex(0);
  widgetHub->updateLabels(bankDisplayed, 0, 0);
  setTheme();

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
  connect(options, SIGNAL(triggered()), this, SLOT(openOptions()));
  connect(credits, SIGNAL(triggered()), this, SLOT(openCredits()));
  connect(widgetAd, SIGNAL(fireCommercial()), this, SLOT(applyFireCommercial()));
  connect(widgetAd, SIGNAL(newCommercial(DragEmployee*)), this, SLOT(applyNewCommercial(DragEmployee*)));
  connect(widgetStock, SIGNAL(setIsActivated(bool)), this, SLOT(applyCommercialIsActivated(bool)));
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
  Item item1("Ariane", 0, 5, 45, 100, ":/Swich/ariane.jpg", 0, 0);
  Item item2("Hubble", 0, 18, 78, 200, ":/Swich/hubble.jpeg", 0, 1);
  Item item3("ISS", 0, 20, 85, 300, ":/Swich/iss.png", 0, 2);

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

  int sizeA = (int)cityList.size();
  int sizeB = (int)itemList.size();
  for (int a = 0; a < sizeA; a++)
  {
    for (int i = 0; i < sizeB; i++)
    {
      cityList.at(a).addToList(itemList.at(i));
    }
  }

  itemList.at(0).setStock(10);
  itemList.at(1).setStock(5);
  itemList.at(2).setStock(0);
}

void Swich::connectToMenu()
{
  auto getSender = qobject_cast<QPushButton*>(sender());
  if (hub == getSender)
  {
    swichZoneWidget->setCurrentIndex(0);
  }
  else if (analytics == getSender)
  {
    swichZoneWidget->setCurrentIndex(1);
  }
  else if (sell == getSender)
  {
    swichZoneWidget->setCurrentIndex(2);
  }
  else if (production == getSender)
  {
    swichZoneWidget->setCurrentIndex(3);
  }
  else if (pub == getSender)
  {
    swichZoneWidget->setCurrentIndex(4);
  }
  else if (stock == getSender)
  {
    swichZoneWidget->setCurrentIndex(5);
  }
  else if (chat == getSender)
  {
    swichZoneWidget->setCurrentIndex(6);
  }
  setTheme();
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
  int addedDays = 25 + Static::randZeroToVal(10);

  //Update Widgets
  QString prod_Cost = widgetProduction->newMonthProd(addedDays);
  QStringList listProd_Cost = prod_Cost.split("$");
  temporaryCharges += listProd_Cost.at(1).toDouble();

  //AD
  QString salary_Efficiency = widgetAd->getSalary_Production(addedDays);
  QStringList splitSalary_Efficiency = salary_Efficiency.split("$");

  //city Sell
  for (int i = 0; i < cityList.size(); i++)
  {
    QStringList getValue = (cityList.at(i).randSells(splitSalary_Efficiency.at(1).toDouble())).split("$");
    temporaryGain += getValue.at(0).toDouble();
    temporarySoldVol += getValue.at(1).toDouble();
  }
  if (gotCommercial && commercialActivated)
  {
    commercialTransfertStock();
    temporaryCharges += (getCommercial->getSalary() / 30) * addedDays;
  }
  temporaryCharges += addProductionToInventory(listProd_Cost.at(0).toDouble());

  temporaryCharges += splitSalary_Efficiency.at(0).toDouble();
  double evoBanque = temporaryGain - temporaryCharges;
  bankDisplayed += temporaryGain - temporaryCharges;

  sold->setText(QString::number(round(bankDisplayed)));
  QString date = widgetHub->updateCurrentMonth(evoBanque, temporarySoldVol, addedDays);
  widgetHub->updateAndScrollWidgets(date, QString::number(round(evoBanque)), QString::number(bankDisplayed));

  widgetAnalytics->updateAnalytics(turnId++, temporarySoldVol, bankDisplayed, temporaryCharges, listProd_Cost.at(0).toDouble());
  widgetHub->updateLabels(bankDisplayed, listProd_Cost.at(0).toDouble(), temporarySoldVol);
  widgetSell->refreshStock();
  widgetStock->updateStock();
}

double Swich::addProductionToInventory(double addedProduction)
{
  int items = (int)itemList.size();
  int nrbIteration = 15 + Static::randZeroToVal(10);
  double prodToPush = addedProduction / nrbIteration;
  double price = 0;

  for (int i = 0; i < nrbIteration; i++)
  {
    int randoItem = Static::randZeroToVal(items);
    itemList.at(randoItem).setStock(itemList.at(randoItem).getStock() + prodToPush);
    price += itemList.at(randoItem).getBuyP() * prodToPush;
  }
  return price;
}

void Swich::applyUpgradeFactory(int cost, int id)
{
  if (cost > bankDisplayed)
  {
    return;
  }
  bankDisplayed -= cost;
  sold->setText(QString::number(round(bankDisplayed)));
  widgetProduction->validatedUpgrade(id);
}

void Swich::applyNewFactory(int cost, int id)
{
  if (cost > bankDisplayed)
  {
    return;
  }
  bankDisplayed -= cost;
  sold->setText(QString::number(round(bankDisplayed)));
  widgetProduction->validateNewFactory(id);
}

void Swich::openOptions()
{
  new Options(this);
}

void Swich::openCredits()
{
  new Credits(this);
}

void Swich::setTheme()
{
  QString backgroundColor = "";
  switch (swichZoneWidget->currentIndex())
  {
    case 0:
      backgroundColor = "#ff5252";
      break;
    case 1:
      backgroundColor = "#7c4dff";
      break;
    case 2:
      backgroundColor = "#536dfe";
      break;
    case 3:
      backgroundColor = "#64ffda";
      break;
    case 4:
      backgroundColor = "#b2ff59";
      break;
    case 5:
      backgroundColor = "#ffd740";
      break;
    case 6:
      backgroundColor = "#ff6e40";
      break;
    default:
      break;
  }

  bar->setStyleSheet("QMenuBar{ background-color:" + backgroundColor + "; color:#262626;} QMenuBar::item:selected{border-top: 2px solid #262626} QMenuBar::item:pressed{background-color:#262626; color:" + backgroundColor + ";}");
}

void Swich::applyNewCommercial(DragEmployee* getActualEmployee)
{
  getCommercial = getActualEmployee;
  gotCommercial = true;
  widgetStock->updateCommercialSlot(getActualEmployee);
}

void Swich::applyFireCommercial()
{
  widgetStock->firedCommercial();
  gotCommercial = false;
  getCommercial = nullptr;
}

void Swich::applyCommercialIsActivated(bool val)
{
  commercialActivated = val;
}

void Swich::commercialTransfertStock()
{
  double nbrItemToTransfert = 3;
  int getLvl = getCommercial->getLvl();
  while (getLvl > 0)
  {
    nbrItemToTransfert *= (1.2 + Static::randOnlyPositivePercentage(50));
    getLvl--;
  }

  int itemsListSize = (int)itemList.size();
  int cityListSize = (int)cityList.size();
  int nrbIteration = 10 + Static::randZeroToVal(10);
  double prodToPush = nbrItemToTransfert / nrbIteration;

  for (int i = 0; i < nrbIteration; i++)
  {
    int randoItem = Static::randZeroToVal(itemsListSize);
    int randoCity = Static::randZeroToVal(cityListSize);

    itemList.at(randoItem).setStock(itemList.at(randoItem).getStock() - prodToPush);
    cityList.at(randoCity).pushStockToList(itemList.at(randoItem).getId(), prodToPush);
  }
  widgetStock->setItemPushed(round(nbrItemToTransfert));
}