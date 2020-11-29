#include "Swich.h"
#include "stdafx.h"

Swich::Swich(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  bankDisplayed = 0;
  gotCommercial = false;
  commercialActivated = true;
  positiveBank = true;

  setDefaultList();
  createDefaultWidget();

  QGridLayout* swichLayout = new QGridLayout(this->ui.centralWidget);
  ini(swichLayout);

  applyTableChanged();
}

void Swich::ini(QGridLayout* layout)
{
  //Menu Bar
  bar = new QMenuBar(this);
  more = new QMenu(tr("More"), this);

  QAction* options = new QAction(tr("Settings"));
  QAction* closeApp = new QAction(tr("Close"));
  QAction* dataAction = new QAction(tr("Database"));
  QAction* tuto = new QAction(tr("Tutorial"));
  QAction* credits = new QAction(tr("Credits"));

  QWidget* cornerWidget = new QWidget(this);
  QHBoxLayout* containCorner = new QHBoxLayout(this);
  actualDb = new QLabel(ItemDAO::getInstance()->getCurrentTable(), this);
  saveButton = new QPushButton(tr("Save"), this);

  this->setMenuBar(bar);
  bar->addMenu(more);

  more->addAction(options);
  more->addAction(dataAction);
  more->addAction(tuto);
  more->addAction(closeApp);
  bar->addAction(credits);
  bar->setCornerWidget(cornerWidget);

  SingleData* data = SingleData::getInstance();

  data->addActionToAdaptOnTheme("settings", options);
  data->addActionToAdaptOnTheme("close", closeApp);
  data->addActionToAdaptOnTheme("database", dataAction);
  data->addActionToAdaptOnTheme("tutorial", tuto);

  options->setIcon(data->getPixMapOnActualTheme("settings"));
  closeApp->setIcon(data->getPixMapOnActualTheme("close"));
  dataAction->setIcon(data->getPixMapOnActualTheme("database"));
  tuto->setIcon(data->getPixMapOnActualTheme("tutorial"));

  saveButton->setIcon(data->getPixmap("downloaddark"));

  cornerWidget->setLayout(containCorner);
  containCorner->addWidget(actualDb);
  containCorner->addWidget(saveButton);

  containCorner->setAlignment(Qt::AlignRight);
  containCorner->setContentsMargins(0, 0, 0, 0);
  cornerWidget->setObjectName("corner");

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
  sold = new QLabel(QString::number(round(bankDisplayed)), this);

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

  hub->setCursor(Qt::PointingHandCursor);
  analytics->setCursor(Qt::PointingHandCursor);
  sell->setCursor(Qt::PointingHandCursor);
  production->setCursor(Qt::PointingHandCursor);
  pub->setCursor(Qt::PointingHandCursor);
  stock->setCursor(Qt::PointingHandCursor);
  chat->setCursor(Qt::PointingHandCursor);
  more->setCursor(Qt::PointingHandCursor);
  saveButton->setCursor(Qt::PointingHandCursor);

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

  sold->setToolTip(tr("Display your actual amount of gold."));

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

  connect(saveButton, SIGNAL(clicked()), this, SLOT(buttonSaveToDatabase()));
  connect(widgetHub, SIGNAL(transfertNewMounth()), this, SLOT(startNewMonth()));
  connect(widgetSell, SIGNAL(callUpdateStock()), this, SLOT(applyUpdateStock()));
  connect(widgetProduction, SIGNAL(transfertUpgrade(int, int)), this, SLOT(applyUpgradeFactory(int, int)));
  connect(widgetProduction, SIGNAL(transfertNewFactory(int, int)), this, SLOT(applyNewFactory(int, int)));
  connect(widgetAd, SIGNAL(fireCommercial()), this, SLOT(applyFireCommercial()));
  connect(widgetAd, SIGNAL(newCommercial(DragEmployee*)), this, SLOT(applyNewCommercial(DragEmployee*)));
  connect(widgetStock, SIGNAL(setIsActivated(bool)), this, SLOT(applyCommercialIsActivated(bool)));
  connect(options, SIGNAL(triggered()), this, SLOT(openOptions()));
  connect(credits, SIGNAL(triggered()), this, SLOT(openCredits()));
  connect(closeApp, SIGNAL(triggered()), this, SLOT(close()));
  connect(dataAction, SIGNAL(triggered()), this, SLOT(openDatabase()));
  connect(tuto, SIGNAL(triggered()), this, SLOT(openTutorial()));

  connect(Tutorial::getInstance(), SIGNAL(tutorialMooved(QPoint)), this, SLOT(applyTutorialMooved(QPoint)));
}

void Swich::createDefaultWidget()
{
  widgetHub = new Hub();
  widgetAnalytics = new Analytics();
  widgetSell = new Sell(cityList, mainItemList);
  widgetProduction = new Production();
  widgetAd = new Ad();
  widgetStock = new Stock(mainItemList);
  widgetChat = new Chat(contactList);
}

void Swich::setDefaultList()
{
  mainItemList = ItemDAO::getInstance()->getItemList();

  City city1(tr("Paris"), 1, ItemDAO::getInstance()->getCityList(0));
  City city2(tr("Tokyo"), 1, ItemDAO::getInstance()->getCityList(1));
  City city3(tr("London"), 1, ItemDAO::getInstance()->getCityList(2));

  cityList.push_back(city1);
  cityList.push_back(city2);
  cityList.push_back(city3);

  Contact contact1("Simon", ":/Swich/images/simon_id.jpg");
  Contact contact2("Bob", "");

  contactList.push_back(contact1);
  contactList.push_back(contact2);

  bankDisplayed = ItemDAO::getInstance()->getBank();
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
    updateNotificationChat(false);
  }
  setTheme();
  widgetSell->cancelWhatNotValidated();
  Tutorial::getInstance()->pageChanged(swichZoneWidget->currentIndex());
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
  int addedDays = 25 + Utils::randZeroToVal(5);

  //Update Widgets
  QStringList listProd_Cost = widgetProduction->newMonthProd(addedDays).split("$");
  temporaryCharges += listProd_Cost.at(1).toDouble();

  //AD
  QStringList splitSalary_Efficiency = widgetAd->getSalary_Production(addedDays).split("$");

  //city Sell
  QStringList getValue = (randSells(splitSalary_Efficiency.at(1).toDouble())).split("$");
  temporaryGain += getValue.at(0).toDouble();
  temporarySoldVol += getValue.at(1).toDouble();

  std::pair<double, int> price_Production = addProductionToInventory(listProd_Cost.at(0).toDouble());
  temporaryCharges += price_Production.first;

  if (gotCommercial && commercialActivated)
  {
    commercialTransfertStock();
    temporaryCharges += (getCommercial->getSalary() / 30.0) * addedDays;
  }

  temporaryCharges += splitSalary_Efficiency.at(0).toDouble();
  double evoBanque = temporaryGain - temporaryCharges;
  bankDisplayed += temporaryGain - temporaryCharges;

  if (bankDisplayed < 0)
  {
    if (positiveBank)
    {
      widgetChat->displayText(0, tr("Take care, you are going wrong !"), 0);
      updateNotificationChat(true);
      positiveBank = false;
    }
  }
  else
  {
    positiveBank = true;
  }

  sold->setText(QString::number(round(bankDisplayed)));
  QString date = widgetHub->updateCurrentMonth(round(evoBanque), temporarySoldVol, addedDays);
  widgetHub->updateAndScrollWidgets(date, QString::number(round(evoBanque)), QString::number(bankDisplayed));

  widgetAnalytics->updateAnalytics(temporarySoldVol, bankDisplayed, temporaryCharges, price_Production.second);
  widgetHub->updateLabels(bankDisplayed, price_Production.second, temporarySoldVol);
  widgetSell->refreshStock();
  widgetStock->updateStock();
}

std::pair<double, int> Swich::addProductionToInventory(double addedProduction)
{
  int items = (int)mainItemList->size();
  int nrbIteration = 10 + Utils::randZeroToVal(10);
  double prodToPush = addedProduction / nrbIteration;
  double price = 0;
  int totalCreatedItems = 0;
  int currentCreatedItems = 0;
  int randoItem = 0;

  for (int i = 0; i < nrbIteration; i++)
  {
    randoItem = Utils::randZeroToVal(items);
    currentCreatedItems = 0;

    currentCreatedItems += mainItemList->at(randoItem).pushProduction(prodToPush);
    price += mainItemList->at(randoItem).getBuyP() * currentCreatedItems;
    totalCreatedItems += currentCreatedItems;
  }
  widgetProduction->pushCreatedItems(totalCreatedItems);
  return std::pair<double, int>(price, totalCreatedItems);
}

QString Swich::randSells(double valAd)
{
  double volToSold = (3.0 + Utils::randZeroToVal(2)) * valAd * 10;
  double newBank = 0;
  double soldQuantity = 0;
  int sizeCityList = (int)cityList.size();

  double parts = 0.0;
  int idCity = 0;
  int idItem = 0;
  int thisSold = 0;
  Item* temporaireItem = new Item();

  int getError = 0;

  while (volToSold > 0)
  {
    thisSold = 0;
    parts = 1.0 + (Utils::randZeroToVal(volToSold) / 4.0);
    idCity = Utils::randZeroToVal(sizeCityList);
    idItem = Utils::randZeroToVal((int)cityList.at(idCity).getList()->size());

    temporaireItem = &cityList.at(idCity).getList()->at(idItem);

    if (temporaireItem->getStock() <= 0)
    {
      getError++;
      if (getError > 100)
      {
        break;
      }
      continue;
    }
    getError = 0;

    thisSold += temporaireItem->pushSales(parts);
    newBank += temporaireItem->getSellP() * thisSold;

    soldQuantity += thisSold;
    volToSold -= parts;
  }
  return QString("%1$%2").arg(newBank).arg(soldQuantity);
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
  Tutorial::getInstance()->pageChanged(7);
  new Options(this);
  Tutorial::getInstance()->pageChanged(swichZoneWidget->currentIndex());
}

void Swich::openCredits()
{
  new Credits(this);
}

void Swich::openDatabase()
{
  Tutorial::getInstance()->pageChanged(8);
  Database* db = new Database(this, swichZoneWidget->currentIndex());
  connect(db, SIGNAL(tableChanged()), this, SLOT(applyTableChanged()));
  db->exec();
  Tutorial::getInstance()->pageChanged(swichZoneWidget->currentIndex());
}

void Swich::openTutorial()
{
  QPoint point(this->geometry().x() + this->width() + 10, this->geometry().y());
  Tutorial::getInstance()->tutorialOpened(swichZoneWidget->currentIndex(), point);
}

void Swich::applyTableChanged()
{
  mainItemList = ItemDAO::getInstance()->getItemList();
  cityList.at(0).setList(ItemDAO::getInstance()->getCityList(0));
  cityList.at(1).setList(ItemDAO::getInstance()->getCityList(1));
  cityList.at(2).setList(ItemDAO::getInstance()->getCityList(2));

  actualDb->setText(ItemDAO::getInstance()->getCurrentTable());
  actualDb->setAlignment(Qt::AlignRight);
  widgetStock->setList();
  applyFireCommercial();

  widgetSell->setList();
  widgetSell->applyNewDBOnTable(cityList.at(0).getList(), cityList.at(1).getList(), cityList.at(2).getList());

  widgetAnalytics->newTableUsed();
  widgetProduction->loadDB();
  widgetAd->setNewTableLoaded();

  bankDisplayed = ItemDAO::getInstance()->getBank();
  sold->setText(QString::number(round(bankDisplayed)));
}

void Swich::buttonSaveToDatabase()
{
  ItemDAO::getInstance()->bankPushToDB(bankDisplayed);
  widgetAnalytics->graphPushToDB();
  widgetProduction->productionPushToDB();
  widgetAd->teamPushToDB();
  ItemDAO::getInstance()->itemListPushToDB(mainItemList, cityList.at(0).getList(), cityList.at(1).getList(), cityList.at(2).getList());
  ItemDAO::getInstance()->saveToDatabase();
}

void Swich::setTheme()
{
  QString backgroundColor = Utils::getThemeOnActualWidget(swichZoneWidget->currentIndex());

  bar->setStyleSheet("QMenuBar{ background-color:" + backgroundColor + "; color:#262626;} QMenuBar::item:selected{border-top: 2px solid #262626} QMenuBar::item:pressed{background-color:#262626; color:" + backgroundColor + ";}");
  more->setStyleSheet("QMenu::item::selected{color:" + backgroundColor + ";}");
  saveButton->setStyleSheet("QPushButton::pressed {color:" + backgroundColor + ";}");
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
  double exo = 5 + Utils::randOnlyPositivePercentage(25);
  double commercialStrenght = 10 * pow(exo, getCommercial->getLvl());

  int itemsListSize = (int)mainItemList->size();
  int cityListSize = (int)cityList.size();

  int tryQuantityPushItem = 0;
  int currentPushedItems = 0;
  int totalPushItems = 0;

  int randoItem = 0;
  int randoCity = 0;

  int getError = 0;
  while (commercialStrenght > 0)
  {
    currentPushedItems = 0;
    tryQuantityPushItem = Utils::randZeroToVal(commercialStrenght);
    randoItem = Utils::randZeroToVal(itemsListSize);
    randoCity = Utils::randZeroToVal(cityListSize);

    currentPushedItems = mainItemList->at(randoItem).pushCommercial(tryQuantityPushItem);
    cityList.at(randoCity).pushStockToList(mainItemList->at(randoItem).getId(), currentPushedItems);

    commercialStrenght -= currentPushedItems * tryQuantityPushItem;
    totalPushItems += currentPushedItems;

    if (currentPushedItems == 0)
    {
      getError++;
      if (getError > 100)
      {
        break;
      }
    }
  }
  widgetStock->setItemPushed(round(totalPushItems));
}

void Swich::updateNotificationChat(bool isVisible)
{
  if (isVisible)
  {
    chat->setIcon(SingleData::getInstance()->getPixmap("notification"));
  }
  else
  {
    chat->setIcon(QPixmap(""));
  }
}

void Swich::applyTutorialMooved(QPoint newPoint)
{
  newPoint.setX(newPoint.x() - (this->width() + 10));
  this->setGeometry(QRect(newPoint, this->size()));
}

void Swich::moveEvent(QMoveEvent* event)
{
  QPoint point(this->geometry().x() + this->width() + 10, this->geometry().y());
  Tutorial::getInstance()->mooved(point);
}

void Swich::resizeEvent(QResizeEvent* event)
{
  QPoint point(this->geometry().x() + this->width() + 10, this->geometry().y());
  Tutorial::getInstance()->mooved(point);
}