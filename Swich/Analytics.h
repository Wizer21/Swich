#pragma once
#include "stdafx.h"
#include <qwidget.h>
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtDataVisualization>
#include <QValueAxis>

using namespace QtCharts;
using namespace QtDataVisualization;

class Analytics : public QWidget
{
  Q_OBJECT

public:
  Analytics();
  void updateAnalytics(int addDay, double addVolumes, double addBank, double addCharges);

private slots:
  void graphVolumes();
  void graphBank();
  void graphCharges();

private:
  QStackedWidget* widgetRight;

  void setAnalytics();
  void createGraph();

  QLineSeries* sellSeries;
  QLineSeries* bankSeries;
  QLineSeries* chargeSeries;

  double maxVolume;
  double maxBank;
  double maxCharges;

  QValueAxis* axeVVolumes;
  QValueAxis* axeHVolumes;
  QValueAxis* axeVBank;
  QValueAxis* axeHBank;
  QValueAxis* axeVCharges;
  QValueAxis* axeHCharges;
};
