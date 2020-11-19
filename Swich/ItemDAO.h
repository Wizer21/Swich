#pragma once
#include "stdafx.h"
#include "Item.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMap>

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
  void iniDB();
  void loadDBToItemList();
  std::vector<Item>* getItemList();

private:
  ItemDAO();
  static ItemDAO* instance;

  std::vector<int> getData_Id;
  std::vector<QString> getData_Name;
  std::vector<int> getData_Stock;
  std::vector<int> getData_BuyP;
  std::vector<int> getData_SellP;

  std::vector<Item>* mainItem_List;
};