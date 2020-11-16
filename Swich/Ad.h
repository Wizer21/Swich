#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "DropEmployee.h"
#include "DragEmployee.h"
#include "Static.h"
#include "SingleData.h"

class Ad : public QWidget
{
  Q_OBJECT

public:
  Ad();
  QString getSalary_Production(int addDays);

private slots:
  void employeChanged(const int& id, const int& pos);
  void commercialChanged(const int& id, const int& pos);
  void employeeToTrash(const int& id, const int& pos);

signals:
  void newCommercial(DragEmployee* actualEmploye);
  void fireCommercial();

private:
  int day;
  void setAd();
  void callNewEmploye();
  int idEmploye;

  QVBoxLayout* widgetNew;
  QLabel* teamValueDisplay;
  QGridLayout* layoutAd;
  QVBoxLayout* layoutcommercial;
  QWidget* displayNewEmploye;
  std::vector<DragEmployee*> employeList;
  std::vector<DragEmployee*> commercialCurrent;
};
