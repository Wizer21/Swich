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

using namespace QtCharts;
using namespace QtDataVisualization;

class Analytics : public QWidget
{
  Q_OBJECT

public:
  Analytics();
  void updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges, double addProduction);
  void setColors(int colorId);

private slots:
  void setDisplayedGraph();

private:
  QStackedWidget* widgetRight;

  void setAnalytics();
  void createGraph();

  QLineSeries* zeroSeries;
  QLineSeries* sellSeries;
  QLineSeries* bankSeries;
  QLineSeries* chargeSeries;
  QLineSeries* productionSeries;

  int idGraph;
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
