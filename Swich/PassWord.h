#pragma once
#include <QDialog>
#include "stdafx.h"
#include "ItemDAO.h"
#include "SingleData.h"

class PassWord : public QDialog
{
  Q_OBJECT

public:
  PassWord(QWidget* parent, QString table);
  ~PassWord();

public slots:
  void eyeClicked();
  void eyeReleased();
  void validButton();

signals:
  void transfertValidPassWord(QString);

private:
  void askForPassword(QGridLayout*);
  QString password;
  QString table;
  QLabel* invalid;
  QPushButton* buttonEye;
  QLineEdit* qlineEdit;
};
