#include "Analytics.h"

Analytics::Analytics()
  : QWidget()
{

  maxVolume = 0;
  maxBank = 0;
  maxCharges = 0;

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
}

void Analytics::updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges)
{
  sellSeries->append(addDay, addVolumes);
  bankSeries->append(addDay, addBank);
  chargeSeries->append(addDay, addCharges);

  axeHVolumes->setMax(addDay * 1.5);
  axeHBank->setMax(addDay * 1.5);
  axeHCharges->setMax(addDay * 1.5);

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