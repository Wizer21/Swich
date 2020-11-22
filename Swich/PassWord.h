#pragma once
#include <QDialog>
#include "stdafx.h"
#include "ItemDAO.h"

class PassWord : public QDialog
{
  Q_OBJECT

public:
  PassWord(QWidget* parent, QString table);
  ~PassWord();

public slots:
  void setHideLineEdit(bool);
  void validButton();

signals:
  void transfertValidPassWord(QString);

private:
  void askForPassword(QGridLayout*);
  QString password;
  QString table;
  QLabel* invalid;
  QLineEdit* qlineEdit;
};
