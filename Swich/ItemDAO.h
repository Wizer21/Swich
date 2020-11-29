#pragma once
#include "stdafx.h"
#include "Item.h"
#include "PassWord.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMap>
#include <QSqlQueryModel>
#include "City.h"
#include "DragEmployee.h"
#include <QDebug>

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

  void itemListPushToDB(std::vector<Item>* itemList, std::vector<Item>* itemCity1, std::vector<Item>* itemCity2, std::vector<Item>* itemCity3);
  void pushGrapgData(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>);
  void bankPushToDB(double newBank);
  void pushFactory(std::vector<std::pair<int, int>>);
  void pushEmployee(std::vector<DragEmployee*> employe, std::vector<DragEmployee*> commercial);

  void saveToDatabase();

  bool isLocked(QString tableName);
  void isUnlocked(QString tableName);

  QStringList getTablesList();
  QString getCurrentTable();
  QString getPassword(QString tableName);
  QSqlQueryModel* getQuerryModel(QString tableName);

  std::vector<Item>* getItemList();
  std::vector<Item>* getCityList(int numberCity);
  std::vector<double> getGraphData(int idGraph);
  std::vector<std::pair<int, int>> getFactory();
  double getBank();
  std::vector<DragEmployee*> getEmployeList();

  void setNewTable(QString name, QString password);
  void deleteTable(QString tableName);

  void addItemToTable(QString table, QString name, double buyP, double sellP);
  void deleteItemToTable(QString tableName, QString itemName);

private:
  ItemDAO();
  void iniDB();
  void setItemId(QString tableName);
  void loadPassword();
  static ItemDAO* instance;
  QSqlDatabase db;
  QString currentTable;

  std::vector<double> sellEvo;
  std::vector<double> bankEvo;
  std::vector<double> taxEvo;
  std::vector<double> productionEvo;

  std::map<QString, bool> lockedList;
  std::map<QString, QString> passwordList;

  std::vector<Item>* mainItem_List;
  std::vector<Item>* mainCity_1;
  std::vector<Item>* mainCity_2;
  std::vector<Item>* mainCity_3;

  double bank;

  std::vector<std::pair<int, int>> factoryLevel_upgrade;

  std::vector<DragEmployee*> employeList;
};