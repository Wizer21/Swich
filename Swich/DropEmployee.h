#pragma once
#include <qwidget.h>
#include "stdafx.h"

class DropEmployee : public QWidget
{
  Q_OBJECT

public:
  DropEmployee(QWidget* parent);
  void setAcceptableType(QString newType);
  void setIsTrash(bool isTrash);

signals:
  void transfertDataEmployee(const int& id, const int& pos);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;

private:
  QString type;
  bool trashable;
};
