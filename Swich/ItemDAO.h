#pragma once
#include "stdafx.h"
#include "Item.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QMap>
#include <QSqlQueryModel>

class ItemDAO
{
public:
  static ItemDAO* getInstance()
  {
    if (!instance)
    {
      instance = new ItemDAO;
    }
    return instance;
  }
  void saveToDatabase();
  QStringList getTablesList();
  std::vector<Item>* getItemList();
  QSqlQueryModel* getQuerryModel(QString tableName);
  void loadDBToItemList(QString tableName);
  bool isDatableOnline();
  QString getCurrentTable();
  void setNewTable(QString name, QString password);
  void deleteTable(QString tableName);
  void addItemToTable(QString table, QString name, int buyP, int sellP);
  void deleteItemToTable(QString tableName, QString itemName);

private:
  ItemDAO();
  void iniDB();
  static ItemDAO* instance;
  QSqlDatabase db;
  QString currentTable;

  std::vector<Item>* mainItem_List;
};