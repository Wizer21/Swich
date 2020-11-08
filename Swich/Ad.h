#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "DragEmployee.h"
#include <QtCharts/QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtDataVisualization>
#include <QValueAxis>
#include "DropEmployee.h"

using namespace QtCharts;
using namespace QtDataVisualization;

class Ad : public QWidget
{
  Q_OBJECT

public:
  Ad();

private slots:
  void employeChanged(QString IdPhoto, int Level, QString Name, QString Talent, int Salary, int id, int pos);

private:
  void setAd();
  QChart* iniGraph();
  void callNewEmploye();
  QLineSeries* sellSeriesAd;
  int idEmploye;

  QValueAxis* axeVVolumesAd;
  QValueAxis* axeHVolumesAd;

  QGridLayout* layoutAd;
  QWidget* displayNewEmploye;
  std::vector<DragEmployee*> employeList;
};
