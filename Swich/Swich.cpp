#include "Swich.h"
#include "stdafx.h"

Swich::Swich(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);
  day = 0;
  // TEMPORAIRE ------------
  a = 10;
  b = 12;
  c = 2;

  QGridLayout* swichLayout = new QGridLayout(this->ui.centralWidget);
  createDefaultWidget();
  ini(swichLayout);
  setDefaultItem();

  // TEMPORAIRE ------------
  widgetAnalytics->updateAnalytics(day++, a++, b++, c++);
  widgetAnalytics->updateAnalytics(day++, a++, b++, c++);
  widgetAnalytics->updateAnalytics(day++, a++, b++, c++);
}

void Swich::ini(QGridLayout* layout)
{
  // Left Band
  QWidget* widgetMenu = new QWidget(this);
  QVBoxLayout* layoutMenu = new QVBoxLayout(this);
  QLabel* swich = new QLabel(tr("Swich"), this);
  QPushButton* hub = new QPushButton(tr("Hub"), this);
  QPushButton* analytics = new QPushButton(tr("Analytics"), this);
  QPushButton* vente = new QPushButton(tr("Sell"), this);
  QPushButton* pub = new QPushButton(tr("Ad"), this);
  QPushButton* entreprise = new QPushButton(tr("Company"), this);
  QPushButton* stock = new QPushButton(tr("Stock"), this);
  QPushButton* message = new QPushButton(tr("Message"), this);

  layout->addWidget(widgetMenu, 0, 0);
  widgetMenu->setLayout(layoutMenu);
  layoutMenu->addWidget(swich);
  layoutMenu->addWidget(hub);
  layoutMenu->addWidget(analytics);
  layoutMenu->addWidget(vente);
  layoutMenu->addWidget(pub);
  layoutMenu->addWidget(entreprise);
  layoutMenu->addWidget(stock);
  layoutMenu->addWidget(message);

  // Right Zone
  swichZoneWidget = new QStackedWidget(this);

  layout->addWidget(swichZoneWidget, 0, 1);

  swichZoneWidget->addWidget(widgetHub);
  swichZoneWidget->addWidget(widgetAnalytics);
  swichZoneWidget->addWidget(widgetSell);
  swichZoneWidget->addWidget(widgetAd);

  swichZoneWidget->setCurrentIndex(0);

  // Set some options
  layoutMenu->setAlignment(Qt::AlignTop);
  swichZoneWidget->setMaximumWidth(this->width() * 0.8);
  swichZoneWidget->setMinimumWidth(this->width() * 0.8);

  // Connection Menu
  connect(hub, SIGNAL(clicked()), this, SLOT(connectToHub()));
  connect(analytics, SIGNAL(clicked()), this, SLOT(connectToAnalytics()));
  connect(vente, SIGNAL(clicked()), this, SLOT(connectToSell()));
  connect(pub, SIGNAL(clicked()), this, SLOT(connectToAd()));
}

void Swich::createDefaultWidget()
{
  widgetHub = new Hub();
  widgetAnalytics = new Analytics();
  widgetSell = new Sell();
  widgetAd = new Ad();
}

void Swich::setDefaultItem()
{
  Item item1("Ariane", 0, 10, 20, 100);
  Item item2("Hubble", 0, 20, 40, 200);
  Item item3("ISS", 0, 30, 50, 300);

  itemList.push_back(item1);
  itemList.push_back(item1);
  itemList.push_back(item1);
}

//Connection Menu Left
void Swich::connectToHub()
{
  swichZoneWidget->setCurrentIndex(0);
}

void Swich::connectToAnalytics()
{
  swichZoneWidget->setCurrentIndex(1);
}

void Swich::connectToSell()
{
  swichZoneWidget->setCurrentIndex(2);
}

void Swich::connectToAd()
{
  swichZoneWidget->setCurrentIndex(3);
}