#include "ItemDAO.h"

ItemDAO::ItemDAO()
{
  mainItem_List = new std::vector<Item>();
  mainCity_1 = new std::vector<Item>();
  mainCity_2 = new std::vector<Item>();
  mainCity_3 = new std::vector<Item>();

  currentTable = "Default Table";
  iniDB();
}

ItemDAO* ItemDAO::instance = 0;

void ItemDAO::iniDB()
{
  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setDatabaseName("swichdb");
  db.setUserName("Wizer");
  db.setPassword("useraccount");

  if (!isDatableOnline())
  {
    Item item1("Ariane", 0, 5, 45, ":/Swich/images/ariane.jpg", 0);
    Item item2("Hubble", 0, 18, 78, ":/Swich/images/hubble.jpeg", 1);
    Item item3("ISS", 0, 20, 85, ":/Swich/images/iss.png", 2);

    mainItem_List->push_back(item1);
    mainItem_List->push_back(item2);
    mainItem_List->push_back(item3);

    currentTable = "Default Table";
  }
  else
  {
    loadDBToLists("SWICHITEM");
    currentTable = "SWICHITEM";
  }
}

bool ItemDAO::isDatableOnline()
{
  bool online = false;
  if (db.open())
  {
    online = true;
  }
  else
  {
    online = false;
  }
  return online;
}

void ItemDAO::loadDBToLists(QString tableName)
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
    int columnCity1 = rec.indexOf("stock_city1");
    int columnCity2 = rec.indexOf("stock_city2");
    int columnCity3 = rec.indexOf("stock_city3");

    // Push to list
    mainItem_List->clear();
    mainCity_1->clear();
    mainCity_2->clear();
    mainCity_3->clear();
    while (queryDB.next())
    {
      mainItem_List->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnStock).toInt(), queryDB.value(columnBuyP).toInt(), queryDB.value(columnSellP).toInt(), "", queryDB.value(columnID).toInt()));
      mainCity_1->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity1).toInt(), queryDB.value(columnSellP).toInt(), queryDB.value(columnID).toInt()));
      mainCity_2->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity2).toInt(), queryDB.value(columnSellP).toInt(), queryDB.value(columnID).toInt()));
      mainCity_3->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity3).toInt(), queryDB.value(columnSellP).toInt(), queryDB.value(columnID).toInt()));
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
      queryDB.prepare(QString("UPDATE %1 SET stock_item = :value, stock_city1 = :city1, stock_city2 = :city2, stock_city3 = :city3 WHERE id_item = :id;").arg(currentTable));

      queryDB.bindValue(":value", mainItem_List->at(i).getStock());
      queryDB.bindValue(":city1", mainCity_1->at(i).getStock());
      queryDB.bindValue(":city2", mainCity_2->at(i).getStock());
      queryDB.bindValue(":city3", mainCity_3->at(i).getStock());
      queryDB.bindValue(":id", mainItem_List->at(i).getId());
      queryDB.exec();
      QString laste = queryDB.lastQuery();
    }
  }
  db.close();
}

void ItemDAO::pushListsToDAO(std::vector<Item>* itemList, std::vector<Item>* itemCity1, std::vector<Item>* itemCity2, std::vector<Item>* itemCity3)
{
  mainItem_List = itemList;
  mainCity_1 = itemCity1;
  mainCity_2 = itemCity2;
  mainCity_3 = itemCity3;
}

QSqlQueryModel* ItemDAO::getQuerryModel(QString tableName)
{
  db.open();
  QSqlQueryModel* getTableData = new QSqlQueryModel();
  getTableData->setQuery(QString("SELECT name_item AS 'Item', stock_item AS 'Stock', buyp_item AS 'Buy.P', sellp_item AS 'Sell.P', stock_city1 AS 'City One', stock_city2 AS 'City Two', stock_city3 AS 'City Three' FROM %1").arg(tableName));
  db.close();
  return getTableData;
}

void ItemDAO::setNewTable(QString name, QString password)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
                       "password_table INT, "
                       "id_item INT UNSIGNED AUTO_INCREMENT, "
                       "name_item TEXT, "
                       "stock_item DOUBLE(10, 3) NOT NULL, "
                       "buyp_item DOUBLE(10, 3), "
                       "sellp_item DOUBLE(10, 3), "

                       "stock_city1 DOUBLE(10, 3) NOT NULL, "
                       "stock_city2 DOUBLE(10, 3) NOT NULL, "
                       "stock_city3 DOUBLE(10, 3) NOT NULL, "
                       "PRIMARY KEY(id_item) "
                       ");")
                 .arg(name));

  if (password != "")
  {
    queryDB.exec(QString("INSERT INTO %1 (password_table) VALUES(%2);").arg(name).arg(password));
  }

  queryDB.exec(QString("INSERT INTO %1 (id_item, name_item, buyp_item, sellp_item ) VALUES(NULL,'chaussette','8','16');").arg(name));

  db.close();
}

void ItemDAO::deleteTable(QString tableName)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.exec(QString("DROP TABLE %1").arg(tableName));
  db.close();
}

std::vector<Item>* ItemDAO::getItemList()
{
  loadDBToLists(currentTable);
  return mainItem_List;
}

std::vector<Item>* ItemDAO::getCityList(int numberCity)
{
  switch (numberCity)
  {
    case 0:
      return mainCity_1;
    case 1:
      return mainCity_2;
    case 2:
      return mainCity_3;
  }
}

QString ItemDAO::getCurrentTable()
{
  return currentTable;
}

void ItemDAO::addItemToTable(QString table, QString name, int buyP, int sellP)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.prepare(QString("INSERT INTO %1 (id_item, name_item, buyp_item, sellp_item ) "
                          "VALUES(NULL, :newName, :newBuyP , :newSellP );")
                    .arg(table));

  queryDB.bindValue(":newName", name);
  queryDB.bindValue(":newBuyP", buyP);
  queryDB.bindValue(":newSellP", sellP);
  queryDB.exec();

  db.close();
}

void ItemDAO::deleteItemToTable(QString tableName, QString itemName)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.exec(QString("DELETE FROM %1 WHERE name_item = '%2';").arg(tableName).arg(itemName));
  db.close();
}

void ItemDAO::setItemId(QString tableName)
{
  db.open();
  QSqlQuery queryDB(db);
  while (queryDB.next())
  {
    queryDB.exec(QString());
  }

  db.close();
}