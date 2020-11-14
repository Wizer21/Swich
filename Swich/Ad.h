#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "DragEmployee.h"
#include "DropEmployee.h"
#include "Static.h"

class Ad : public QWidget
{
  Q_OBJECT

public:
  Ad();
  QString getSalary_Production(int addDays);

private slots:
  void employeChanged(const int& id, const int& pos);

private:
  int day;
  void setAd();
  void callNewEmploye();
  void setTotalLvl();
  int idEmploye;

  QLabel* teamValueDisplay;
  QGridLayout* layoutAd;
  QWidget* displayNewEmploye;
  std::vector<DragEmployee*> employeList;
};
