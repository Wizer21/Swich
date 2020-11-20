#pragma once
#include "stdafx.h"
#include <QDialog>
#include "ItemDAO.h"

class Database : public QDialog
{
  Q_OBJECT

public:
  Database(QWidget* parent);
  ~Database();

private:
  void iniDB(QGridLayout* layout);
};
