#include "ItemDAO.h"

ItemDAO::ItemDAO()
{
  mainItem_List = new std::vector<Item>();
  currentTable = "";
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
    loadDBToItemList("SWICHITEM");
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
  getTableData->setQuery(QString("SELECT name_item AS 'Item', stock_item AS 'Stock', buyp_item AS 'Buy.P', sellp_item AS 'Sell.P' FROM %1").arg(tableName));
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
                       "stock_item DOUBLE(10, 3), "
                       "buyp_item DOUBLE(10, 3), "
                       "sellp_item DOUBLE(10, 3), "

                       "PRIMARY KEY(id_item) "
                       ");")
                 .arg(name));

  if (password != "")
  {
    queryDB.exec(QString("INSERT INTO %1 (password_table) VALUES(%2);").arg(name).arg(password));
  }

  queryDB.exec(QString("INSERT INTO %1 (id_item, name_item, stock_item, buyp_item, sellp_item ) VALUES(NULL, 'chaussette','2.2' ,'8','16');").arg(name));

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
  loadDBToItemList(currentTable);
  return mainItem_List;
}

QString ItemDAO::getCurrentTable()
{
  return currentTable;
}

void ItemDAO::addItemToTable(QString table, QString name, int buyP, int sellP)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.prepare(QString("INSERT INTO %1 (id_item, name_item, stock_item, buyp_item, sellp_item ) "
                          "VALUES(NULL, :newName , 0 , :newBuyP , :newSellP );")
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