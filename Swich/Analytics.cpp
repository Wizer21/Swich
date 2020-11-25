#include "Analytics.h"

Analytics::Analytics()
  : QWidget()
{
  maxVolume = 0;
  maxBank = 0;
  maxCharges = 0;
  idGraph = 0;
  minBank = 0;

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

  widgetList->setAlignment(Qt::AlignCenter);
  widgetRight->setCurrentIndex(1);

  volVente->setCursor(Qt::PointingHandCursor);
  evoBanque->setCursor(Qt::PointingHandCursor);
  evoCharges->setCursor(Qt::PointingHandCursor);
  evoProduction->setCursor(Qt::PointingHandCursor);
  connect(volVente, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoBanque, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoCharges, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
  connect(evoProduction, SIGNAL(clicked()), this, SLOT(setDisplayedGraph()));
}

void Analytics::createGraph()
{
  // Sell Volumes

  sellVolume = new QChart();

  sellSeries = new QLineSeries();
  sellSeries->setName(tr("Sales Volumes"));

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
  bank = new QChart();

  zeroSeries = new QLineSeries();
  bankSeries = new QLineSeries();
  bankSeries->setName(tr("Bank"));
  zeroSeries->setPen(QPen(QColor(255, 215, 64, 255)));

  bank->addSeries(bankSeries);
  bank->addSeries(zeroSeries);

  axeVBank = new QValueAxis(this);
  axeHBank = new QValueAxis(this);

  bank->addAxis(axeVBank, Qt::AlignLeft);
  bank->addAxis(axeHBank, Qt::AlignBottom);

  bankSeries->attachAxis(axeVBank);
  bankSeries->attachAxis(axeHBank);
  zeroSeries->attachAxis(axeVBank);
  zeroSeries->attachAxis(axeHBank);

  QChartView* viewerBanque = new QChartView(bank);

  widgetRight->addWidget(viewerBanque);

  // Evo Charges

  charge = new QChart();

  chargeSeries = new QLineSeries();
  chargeSeries->setName(tr("Charges"));

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

  production = new QChart();

  productionSeries = new QLineSeries();
  productionSeries->setName(tr("Production"));

  production->addSeries(productionSeries);

  axeVProduction = new QValueAxis(this);
  axeHProduction = new QValueAxis(this);

  production->addAxis(axeVProduction, Qt::AlignLeft);
  production->addAxis(axeHProduction, Qt::AlignBottom);

  productionSeries->attachAxis(axeVProduction);
  productionSeries->attachAxis(axeHProduction);

  QChartView* viewerProduction = new QChartView(production);

  widgetRight->addWidget(viewerProduction);

  setColors(1);
}

void Analytics::updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges, double addProduction)
{
  sellEvo.push_back(addVolumes);
  bankEvo.push_back(addBank);
  taxEvo.push_back(addCharges);
  productionEvo.push_back(addProduction);

  pushDataToGraph(addDay, addVolumes, addBank, addCharges, addProduction);
}

void Analytics::pushDataToGraph(int addDay, double addVolumes, double addBank, double addCharges, double addProduction)
{

  sellSeries->append(addDay, addVolumes);
  bankSeries->append(addDay, addBank);
  zeroSeries->append(addDay * 1.5, 0);
  chargeSeries->append(addDay, addCharges);
  productionSeries->append(addDay, addProduction);

  axeHVolumes->setMax(addDay * 1.5);
  axeHBank->setMax(addDay * 1.5);
  axeHCharges->setMax(addDay * 1.5);
  axeHProduction->setMax(addDay * 1.5);

  if (minBank > addBank)
  {
    axeVBank->setMin(addBank * 1.5);
    minBank = addBank;
  }
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

void Analytics::setColors(int id)
{
  QString color = "";
  switch (id)
  {
    case 0:
      color = "black";
      break;
    case 1:
      color = "white";
      break;
    default:
      break;
  }

  sellVolume->setBackgroundVisible(false);
  sellSeries->setColor(QColor(83, 109, 254));
  axeVVolumes->setLabelsColor(QColor(color));
  axeHVolumes->setLabelsColor(QColor(color));
  QLegend* legendVolume = sellVolume->legend();
  legendVolume->setLabelColor(QColor(color));

  bank->setBackgroundVisible(false);
  bankSeries->setColor(QColor(255, 82, 82));
  axeVBank->setLabelsColor(QColor(color));
  axeHBank->setLabelsColor(QColor(color));
  QLegend* legendBank = bank->legend();
  legendBank->setLabelColor(QColor(color));

  charge->setBackgroundVisible(false);
  chargeSeries->setColor(QColor(178, 255, 89));
  axeVCharges->setLabelsColor(QColor(color));
  axeHCharges->setLabelsColor(QColor(color));
  QLegend* legendCharges = charge->legend();
  legendCharges->setLabelColor(QColor(color));

  production->setBackgroundVisible(false);
  productionSeries->setColor(QColor(100, 255, 218));
  axeVProduction->setLabelsColor(QColor(color));
  axeHProduction->setLabelsColor(QColor(color));
  QLegend* legendProduction = production->legend();
  legendProduction->setLabelColor(QColor(color));
}

void Analytics::graphPushToDB()
{
  ItemDAO::getInstance()->pushGrapgData(sellEvo, bankEvo, taxEvo, productionEvo);
}

void Analytics::newTableUsed()
{
  sellEvo = ItemDAO::getInstance()->getGraphData(0);
  bankEvo = ItemDAO::getInstance()->getGraphData(1);
  taxEvo = ItemDAO::getInstance()->getGraphData(2);
  productionEvo = ItemDAO::getInstance()->getGraphData(3);

  sellSeries->clear();
  bankSeries->clear();
  chargeSeries->clear();
  productionSeries->clear();

  minBank = 0;
  maxVolume = 0;
  maxBank = 0;
  maxCharges = 0;
  maxProduction = 0;

  int iteration = 0;
  int dataSize = (int)sellEvo.size();
  for (int i = 0; i < dataSize; i++)
  {
    pushDataToGraph(iteration++, sellEvo.at(i), bankEvo.at(i), taxEvo.at(i), productionEvo.at(i));
  }
}