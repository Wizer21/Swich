#include "Analytics.h"

Analytics::Analytics()
  : QWidget()
{

  maxVolume = 0;
  maxBank = 0;
  maxCharges = 0;
  idGraph = 0;

  setAnalytics();
  createGraph();
}

void Analytics::setAnalytics()
{
  QGridLayout* layoutAnalytics = new QGridLayout(this);

  QWidget* widgetMenuLeft = new QWidget(this);
  QVBoxLayout* widgetList = new QVBoxLayout(this);
  QPushButton* volVente = new QPushButton(tr("Sell volume"), this);
  QPushButton* evoBanque = new QPushButton(tr("Bank"), this);
  QPushButton* evoCharges = new QPushButton(tr("Tax volume"), this);
  QPushButton* evoProduction = new QPushButton(tr("Production"), this);

  widgetRight = new QStackedWidget(this);

  this->setLayout(layoutAnalytics);

  layoutAnalytics->addWidget(widgetMenuLeft, 0, 0);
  widgetMenuLeft->setLayout(widgetList);
  widgetList->addWidget(volVente);
  widgetList->addWidget(evoBanque);
  widgetList->addWidget(evoCharges);
  widgetList->addWidget(evoProduction);

  layoutAnalytics->addWidget(widgetRight, 0, 1);

  volVente->setObjectName(QString::number(idGraph++));
  evoBanque->setObjectName(QString::number(idGraph++));
  evoCharges->setObjectName(QString::number(idGraph++));
  evoProduction->setObjectName(QString::number(idGraph++));

  widgetRight->setCurrentIndex(1);

  connect(volVente, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoBanque, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoCharges, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoProduction, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
}

void Analytics::createGraph()
{
  // Sell Volumes

  QChart* sellVolume = new QChart();

  sellSeries = new QLineSeries();

  sellVolume->addSeries(sellSeries);

  axeVVolumes = new QValueAxis(this);
  axeHVolumes = new QValueAxis(this);

  sellVolume->addAxis(axeVVolumes, Qt::AlignLeft);
  sellVolume->addAxis(axeHVolumes, Qt::AlignBottom);

  sellSeries->attachAxis(axeVVolumes);
  sellSeries->attachAxis(axeHVolumes);

  QChartView* viewerSell = new QChartView(sellVolume);

  widgetRight->addWidget(viewerSell);

  // Banque Graph
  QChart* bank = new QChart();

  bankSeries = new QLineSeries();

  bank->addSeries(bankSeries);

  axeVBank = new QValueAxis(this);
  axeHBank = new QValueAxis(this);

  bank->addAxis(axeVBank, Qt::AlignLeft);
  bank->addAxis(axeHBank, Qt::AlignBottom);

  bankSeries->attachAxis(axeVBank);
  bankSeries->attachAxis(axeHBank);

  QChartView* viewerBanque = new QChartView(bank);

  widgetRight->addWidget(viewerBanque);

  // Evo Charges

  QChart* charge = new QChart();

  chargeSeries = new QLineSeries();

  charge->addSeries(chargeSeries);

  axeVCharges = new QValueAxis(this);
  axeHCharges = new QValueAxis(this);

  charge->addAxis(axeVCharges, Qt::AlignLeft);
  charge->addAxis(axeHCharges, Qt::AlignBottom);

  chargeSeries->attachAxis(axeVCharges);
  chargeSeries->attachAxis(axeHCharges);

  QChartView* viewerCharges = new QChartView(charge);

  widgetRight->addWidget(viewerCharges);

  // Evo Charges

  QChart* production = new QChart();

  productionSeries = new QLineSeries();

  production->addSeries(productionSeries);

  axeVProduction = new QValueAxis(this);
  axeHProduction = new QValueAxis(this);

  production->addAxis(axeVProduction, Qt::AlignLeft);
  production->addAxis(axeHProduction, Qt::AlignBottom);

  productionSeries->attachAxis(axeVProduction);
  productionSeries->attachAxis(axeHProduction);

  QChartView* viewerProduction = new QChartView(production);

  widgetRight->addWidget(viewerProduction);
}

void Analytics::updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges, double addProduction)
{
  sellSeries->append(addDay, addVolumes);
  bankSeries->append(addDay, addBank);
  chargeSeries->append(addDay, addCharges);
  productionSeries->append(addDay, addProduction);

  axeHVolumes->setMax(addDay * 1.5);
  axeHBank->setMax(addDay * 1.5);
  axeHCharges->setMax(addDay * 1.5);
  axeHProduction->setMax(addDay * 1.5);

  if (addVolumes > maxVolume)
  {
    maxVolume = addVolumes;
    axeVVolumes->setMax(addVolumes * 1.5);
  }

  if (addBank > maxBank)
  {
    maxBank = addBank;
    axeVBank->setMax(addBank * 1.5);
  }

  if (addCharges > maxCharges)
  {
    maxCharges = addCharges;
    axeVCharges->setMax(addCharges * 1.5);
  }
  if (addProduction > maxProduction)
  {
    maxProduction = addProduction;
    axeVProduction->setMax(addProduction * 1.5);
  }
}

void Analytics::setDisplayedGraph()
{
  widgetRight->setCurrentIndex(sender()->objectName().toInt());
}
