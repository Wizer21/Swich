#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "SingleData.h"
#include <cmath>

class Hub : public QWidget
{
  Q_OBJECT

public:
  Hub();
  void updateLabels(double addBank, double addProd, double addSell);
  QString updateCurrentMonth(int gain, int sells, int addDays);
  void updateAndScrollWidgets(QString date, QString gain, QString bank);

public slots:
  void newMonthClicked();

signals:
  void transfertNewMounth();

private:
  void setHub();
  void setDefaultWidgets();
  void setColorScroll();

  QLabel* bankMax;
  QLabel* prodMax;
  QLabel* sellsMax;

  double storeMaxBank;
  double storeMaxProd;
  double storeMaxSell;

  QLabel* displayGain;
  QLabel* displaySells;
  QLabel* displayDate;

  int day;
  int month;
  int year;

  QGridLayout* layoutGridBot;

  QString date_1;
  QString gain_1;
  QString bank_1;

  std::vector<QLabel*> date;
  std::vector<QLabel*> gain;
  std::vector<QLabel*> bank;
};
