#pragma once
#include <qwidget.h>
#include "stdafx.h"

class Hub : public QWidget
{
  Q_OBJECT

public:
  Hub();
  void updateLabels(std::vector<double> bankHisto, std::vector<double> volHisto);
  QString updateCurrentMonth(int gain, int sells, int addDays);
  void updateAndScrollWidgets(QString date, QString gain, QString bank);

public slots:
  void newMonthClicked();

signals:
  void transfertNewMounth();

private:
  void setHub();
  void setDefaultWidgets();

  QLabel* bankEvo;
  QLabel* prodEvo;
  QLabel* sellsEvo;

  QLineEdit* displayGain;
  QLineEdit* displaySells;
  QLineEdit* displayDate;

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
