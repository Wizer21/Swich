#pragma once
#include "stdafx.h"
#include <QDialog>
#include "ItemDAO.h"
#include "SingleData.h"
#include "NewTable.h"

class Database : public QDialog
{
  Q_OBJECT

public:
  Database(QWidget* parent);
  ~Database();

public slots:
  void setWidgetToDisplay();
  void loadNewTable();
  void createNewTable();
  void connectNewTable(QString name, QString password);

private:
  void iniDB(QGridLayout* layout);
  void loadTableList();
  void createTableWidgets(QString tableName);

  QVBoxLayout* layoutInScrollArea;
  QStackedWidget* widgetStack;
  QLabel* runningTable;
};
