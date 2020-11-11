#pragma once
#include <QObject>
#include "stdafx.h"

class Options : public QDialog
{
  Q_OBJECT

public:
  Options(QWidget* parent);
  ~Options();

private slots:
  void newFont();
  void setTheme(int index);

private:
  void ini(QVBoxLayout* layout);
};
