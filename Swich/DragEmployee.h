#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Static.h"

class DragEmployee : public QWidget
{

public:
  DragEmployee();
  DragEmployee(QString addIdPhoto, int addLevel, QString addName, QString addNote, int addSalary, int addId, int addPos);
  DragEmployee(QString addIdPhoto, QString addName, QString addNote);
  int getId();
  int getPos();
  int getSalary();
  int getLvl();
  void setPos(int pos);
  QString calculNote(int lvl);

protected:
  void mouseMoveEvent(QMouseEvent* event);

private:
  QString idPhoto;
  int level;
  QString name;
  QString note;
  int salary;
  int id;
  int pos;

  void calculRandStats();
  void ini();
};
