#pragma once
#include "stdafx.h"

class DropWidget : public QScrollArea
{
  Q_OBJECT

public:
  DropWidget(QWidget* parent);

signals:
  void transfertData(QString nom, QString vol, int id);

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dragMoveEvent(QDragMoveEvent* event) override;
  void dropEvent(QDropEvent* event) override;
};