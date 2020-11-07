#pragma once
#include <QDialog>
#include "stdafx.h"

class Credits : public QDialog
{
  Q_OBJECT

public:
  Credits(QWidget* parent);
  void ini(QVBoxLayout* layout);
  ~Credits();
};
