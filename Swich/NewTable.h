#pragma once
#include "stdafx.h"
#include <QDialog>
#include "ItemDAO.h"

class NewTable : public QDialog
{
  Q_OBJECT

public:
  NewTable(QWidget* parent);
  ~NewTable();

public slots:
  void validatePressed();

signals:
  void transfertNewTable(QString name, QString password);

private:
  QLabel* errorMessage;
  QLineEdit* containName;
  QLineEdit* containPassword;
  void ini(QGridLayout* layout);
};
