#pragma once
#include <qwidget.h>
#include "stdafx.h"

class DragEmployee : public QWidget
{

public:
  DragEmployee(DragEmployee* getEmploye);
  DragEmployee(QString addIdPhoto, int addLevel, QString addName, QString addTalent, int addSalary, int addId, int addPos);
  int getId();
  int getPos();
  void setPos(int pos);

protected:
  void mouseMoveEvent(QMouseEvent* event);

private:
  QString idPhoto;
  int level;
  QString name;
  QString talent;
  int salary;
  int id;
  int pos;

  void ini();
};
