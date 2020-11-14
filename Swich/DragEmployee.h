#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Static.h"
#include <QPair>

class DragEmployee : public QWidget
{

public:
  DragEmployee();
  int getId();
  int getPos();
  int getSalary();
  int getLvl();
  void setPos(int pos);
  QString calculNote(int lvl);

protected:
  void mouseMoveEvent(QMouseEvent* event);

private:
  int level;
  QString name;
  QString note;
  int salary;
  int id;
  int pos;

  void calculRandStats();
  void ini(const QPixmap* pix);
};
