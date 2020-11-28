#pragma once
#include "stdafx.h"
#include <qwidget.h>
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtDataVisualization>
#include <QValueAxis>
#include <QCategoryAxis>
#include <QSplineSeries>
#include "ItemDAO.h"

using namespace QtCharts;
using namespace QtDataVisualization;

class Analytics : public QWidget
{
  Q_OBJECT

public:
  Analytics();
  void updateAnalytics(double addVolumes, double addBank, double addCharges, double addProduction);
  void setColors(int colorId);
  void graphPushToDB();
  void newTableUsed();

private slots:
  void setDisplayedGraph();

private:
  QStackedWidget* widgetRight;

  void setAnalytics();
  void createGraph();
  void pushDataToGraph(double addVolumes, double addBank, double addCharges, double addProduction);

  QLineSeries* zeroSeries;
  QLineSeries* sellSeries;
  QLineSeries* bankSeries;
  QLineSeries* chargeSeries;
  QLineSeries* productionSeries;

  std::vector<double> sellEvo;
  std::vector<double> bankEvo;
  std::vector<double> taxEvo;
  std::vector<double> productionEvo;

  int idGraph;
  int currentDay;
  double minBank;
  double maxVolume;
  double maxBank;
  double maxCharges;
  double maxProduction;

  QChart* sellVolume;
  QChart* bank;
  QChart* charge;
  QChart* production;

  QValueAxis* axeVVolumes;
  QValueAxis* axeHVolumes;
  QValueAxis* axeVBank;
  QValueAxis* axeHBank;
  QValueAxis* axeVCharges;
  QValueAxis* axeHCharges;
  QValueAxis* axeVProduction;
  QValueAxis* axeHProduction;
};
