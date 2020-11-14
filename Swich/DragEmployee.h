#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Static.h"
#include "SingleData.h"

class DragEmployee : public QWidget
{

public:
  DragEmployee();
  int getId();
  int getPos();
  int getSalary();
  int getLvl();
  QString getName();
  void setPos(int pos);
  void setId(int newId);
  void setTrashable(bool canBeFire);
  QString calculNote(int lvl);

protected:
  void mouseMoveEvent(QMouseEvent* event);

private:
  int level;
  QString name;
  QString note;
  int salary;
  QString fonction;
  int id;
  int pos;
  bool canBeTrash;

  void calculRandStats();
  void ini(const QPixmap pix);
};
