#pragma once
#include <QDialog>
#include "stdafx.h"

class CreateNewItem : public QDialog
{
  Q_OBJECT

public:
  CreateNewItem(QWidget* parent, QString tableUsed);
  ~CreateNewItem();

public slots:
  void updateFromBuyP(QString value);
  void updateFromSellP(QString value);
  void validateButton();

signals:
  void transfertNewItem(QString table, QString name, int buyp, int sellp);

private:
  QString tableToAdd;

  QLineEdit* containName;
  QLineEdit* containSellP;
  QLineEdit* containBuyp;
  void ini(QGridLayout* layout);
};
