#pragma once
#include <QDialog>
#include "stdafx.h"
#include "SingleData.h"

class Credits : public QDialog
{
  Q_OBJECT

public:
  Credits(QWidget* parent);
  void ini(QHBoxLayout* layout);
  ~Credits();
};
