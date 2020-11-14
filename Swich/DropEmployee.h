#pragma once
#include <qwidget.h>
#include "stdafx.h"

class DropEmployee : public QWidget
{
  Q_OBJECT

public:
  DropEmployee(QWidget* parent);

signals:
  void transfertDataEmployee(const int& id, const int& pos);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
};
