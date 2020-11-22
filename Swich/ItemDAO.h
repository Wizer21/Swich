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

  bool isDatableOnline();
  void loadDBToLists(QString tableName);
  void pushListsToDAO(std::vector<Item>* itemList, std::vector<Item>* itemCity1, std::vector<Item>* itemCity2, std::vector<Item>* itemCity3);
  void pushGrapgData(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>);
  void saveToDatabase();

  QStringList getTablesList();
  QString getCurrentTable();

  std::vector<Item>* getItemList();
  std::vector<Item>* getCityList(int numberCity);
  std::vector<double> getGraphData(int idGraph);

  QSqlQueryModel* getQuerryModel(QString tableName);

  void setNewTable(QString name, QString password);
  void deleteTable(QString tableName);

  void addItemToTable(QString table, QString name, int buyP, int sellP);
  void deleteItemToTable(QString tableName, QString itemName);

private:
  ItemDAO();
  void iniDB();
  void setItemId(QString tableName);
  static ItemDAO* instance;
  QSqlDatabase db;
  QString currentTable;

  std::vector<double> sellEvo;
  std::vector<double> bankEvo;
  std::vector<double> taxEvo;
  std::vector<double> productionEvo;

  std::vector<Item>* mainItem_List;
  std::vector<Item>* mainCity_1;
  std::vector<Item>* mainCity_2;
  std::vector<Item>* mainCity_3;
};