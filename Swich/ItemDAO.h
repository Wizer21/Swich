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

private:
  ItemDAO();
  void iniDB();
  static ItemDAO* instance;
  QSqlDatabase db;
  QString currentTable;

  std::vector<Item>* mainItem_List;
};