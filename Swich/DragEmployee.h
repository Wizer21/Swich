#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Static.h"

class DragEmployee : public QWidget
{

public:
  DragEmployee(QString addIdPhoto, int addLevel, QString addName, QString addTalent, int addSalary, int addId, int addPos);
  DragEmployee(QString addIdPhoto, QString addName, QString addTalent);
  int getId();
  int getPos();
  int getSalary();
  int getLvl();
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

  void calculRandStats();
  void ini();
};
