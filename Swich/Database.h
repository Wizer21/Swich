#pragma once
#include "stdafx.h"
#include <QDialog>
#include "ItemDAO.h"
#include "SingleData.h"
#include "NewTable.h"
#include "CreateNewItem.h"
#include "PassWord.h"
#include "StructSettings.h"

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
  void createItem();
  void applyNewItem(QString table, QString name, double buyP, double sellP);
  void deleteNewItem();
  void passwordValidated(QString tableName);

signals:
  void tableChanged();

private:
  void iniDB(QGridLayout* layout);
  void addTableToList(QString tableName);
  void createTableWidgets(QString tableName);
  void sortItemList();
  void closeEvent(QCloseEvent* e) override;
  void updateLockIcon();

  QLabel* errorMessage;
  QVBoxLayout* layoutInScrollArea;
  QStackedWidget* widgetStack;
  QLabel* runningTable;
  std::map<QString, QWidget*> widgetList;
  std::vector<QPushButton*> buttonList;
};
