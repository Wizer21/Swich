#include "ItemDAO.h"

ItemDAO::ItemDAO()
{
  mainItem_List = new std::vector<Item>();
  currentTable = "";
  iniDB();
  loadDBToItemList("SWICHITEM");
}

ItemDAO* ItemDAO::instance = 0;

void ItemDAO::iniDB()
{
  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("swichdb");
  db.setUserName("Wizer");
  db.setPassword("useraccount");
}

void ItemDAO::loadDBToItemList(QString tableName)
{
  if (currentTable != "")
  {
    saveToDatabase();
  }

  if (db.open())
  {
    QSqlQuery queryDB(db);
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName));

    QSqlRecord rec = queryDB.record();

    // Get Column ID
    int columnID = rec.indexOf("id_item");
    int columnName = rec.indexOf("name_item");
    int columnStock = rec.indexOf("stock_item");
    int columnBuyP = rec.indexOf("buyp_item");
    int columnSellP = rec.indexOf("sellp_item");

    // Push to list
    mainItem_List->clear();
    while (queryDB.next())
    {
      mainItem_List->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnStock).toInt(), queryDB.value(columnBuyP).toInt(), queryDB.value(columnSellP).toInt(), "", queryDB.value(columnID).toInt()));
    }
    currentTable = tableName;
    db.close();
  }
}

QStringList ItemDAO::getTablesList()
{
  if (db.open())
  {
    QStringList tableList = db.tables();
    db.close();
    return tableList;
  }
  return QStringList();
}

void ItemDAO::saveToDatabase()
{
  if (db.open())
  {
    QSqlQuery queryDB(db);

    int sizeList = (int)mainItem_List->size();
    for (int i = 0; i < sizeList; i++)
    {
      queryDB.prepare(QString("UPDATE %1 SET stock_item = :value WHERE id_item = :id;").arg(currentTable));

      queryDB.bindValue(":value", mainItem_List->at(i).getStock());
      queryDB.bindValue(":id", i + 1);
      queryDB.exec();
      QString laste = queryDB.lastQuery();
    }
  }
  db.close();
}

QSqlQueryModel* ItemDAO::getQuerryModel(QString tableName)
{
  db.open();
  QSqlQueryModel* getTableData = new QSqlQueryModel();
  getTableData->setQuery(QString("SELECT * FROM %1;").arg(tableName));

  db.close();
  return getTableData;
}

std::vector<Item>* ItemDAO::getItemList()
{
  return mainItem_List;
}
