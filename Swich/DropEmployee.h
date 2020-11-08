#pragma once
#include <qwidget.h>
#include "stdafx.h"

class DropEmployee : public QWidget
{
  Q_OBJECT

public:
  DropEmployee(QWidget* parent);

signals:
  void transfertDataEmployee(QString IdPhoto, int Level, QString Name, QString Talent, int Salary, int id, int pos);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
};
