#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Utils.h"
#include "SingleData.h"

class DragEmployee : public QWidget
{
public:
  DragEmployee();
  DragEmployee(QString newName, int newSalary, int newLevel, bool newIsCommercial);
  ;
  int getId();
  int getPos();
  int getSalary();
  int getLvl();
  QString getName();
  bool getIsCommercial();
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
  bool isCommercial;
  int id;
  int pos;
  bool canBeTrash;

  void calculRandStats();
  void ini(const QPixmap pix);
  void setBackgroundColor();
};
