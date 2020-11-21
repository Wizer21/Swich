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
  void deleteTableConfirm();

private:
  void iniDB(QGridLayout* layout);
  void addTableToList(QString tableName);
  void createTableWidgets(QString tableName);
  void sortItemList();

  QVBoxLayout* layoutInScrollArea;
  QStackedWidget* widgetStack;
  QLabel* runningTable;
  std::map<QString, QWidget*> widgetList;
  std::vector<QPushButton*> buttonList;
};
