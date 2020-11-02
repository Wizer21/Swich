#include "Analytics.h"

Analytics::Analytics()
  : QWidget()
{
  setAnalytics();
  createGraph();
  graphBank();
}

void Analytics::setAnalytics()
{
  QGridLayout* layoutAnalytics = new QGridLayout(this);

  QWidget* widgetMenuLeft = new QWidget(this);
  QVBoxLayout* widgetList = new QVBoxLayout(this);
  QPushButton* volVente = new QPushButton(tr("Sell volume"), this);
  QPushButton* evoBanque = new QPushButton(tr("Bank"), this);
  QPushButton* evoCharges = new QPushButton(tr("Tax volume"), this);

  widgetRight = new QStackedWidget(this);

  this->setLayout(layoutAnalytics);

  layoutAnalytics->addWidget(widgetMenuLeft, 0, 0);
  widgetMenuLeft->setLayout(widgetList);
  widgetList->addWidget(volVente);
  widgetList->addWidget(evoBanque);
  widgetList->addWidget(evoCharges);

  layoutAnalytics->addWidget(widgetRight, 0, 1);

  connect(volVente, SIGNAL(clicked()), this, SLOT(graphVolumes()));
  connect(evoBanque, SIGNAL(clicked()), this, SLOT(graphBank()));
  connect(evoCharges, SIGNAL(clicked()), this, SLOT(graphCharges()));
}

void Analytics::createGraph()
{
  // Sell Volumes

  QChart* sellVolume = new QChart();

  sellSeries = new QLineSeries();

  sellVolume->addSeries(sellSeries);
  sellVolume->createDefaultAxes();

  QChartView* viewerSell = new QChartView(sellVolume);

  // Banque Graph
  QChart* bank = new QChart();

  bankSeries = new QLineSeries();

  bank->addSeries(bankSeries);
  bank->createDefaultAxes();

  QChartView* viewerBanque = new QChartView(bank);

  widgetRight->addWidget(viewerBanque);

  // Evo Charges

  QChart* charge = new QChart();

  chargeSeries = new QLineSeries();

  charge->addSeries(chargeSeries);
  charge->createDefaultAxes();

  QChartView* viewerCharges = new QChartView(charge);

  widgetRight->addWidget(viewerCharges);
}

void Analytics::updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges)
{
  sellSeries->append(addDay, addVolumes);
  bankSeries->append(addDay, addBank);
  chargeSeries->append(addDay, addCharges);
}

void Analytics::graphVolumes()
{
  widgetRight->setCurrentIndex(0);
}

void Analytics::graphBank()
{
  widgetRight->setCurrentIndex(1);
}

void Analytics::graphCharges()
{
  widgetRight->setCurrentIndex(2);
}