#pragma once
#include "stdafx.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
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

private:
  ItemDAO();
  static ItemDAO* instance;
};