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
  db.setHostName("82.165.206.74");
  db.setDatabaseName("swich_database");
  db.setUserName("swich_user");
  db.setPassword("dev-pwd");

  if (!isDatableOnline() || getTablesList().size() == 0)
  {
    Item item1("Ariane", 0, 5, 45, ":/Swich/images/ariane.jpg", 0);
    Item item2("Hubble", 0, 18, 78, ":/Swich/images/hubble.jpeg", 1);
    Item item3("ISS", 0, 20, 85, ":/Swich/images/iss.png", 2);

    mainItem_List->push_back(item1);
    mainItem_List->push_back(item2);
    mainItem_List->push_back(item3);

    currentTable = "Default Table";

    bank = 11327;
  }
  else
  {
    loadDBToLists(getTablesList().at(0));
    currentTable = getTablesList().at(0);
    loadPassword();
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
  if (db.open())
  {
    // LOAD ITEM LIST
    QSqlQuery queryDB(db);
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName));

    QSqlRecord rec = queryDB.record();

    int columnID = rec.indexOf("id_item");
    int columnName = rec.indexOf("name_item");
    int columnStock = rec.indexOf("stock_item");
    int columnBuyP = rec.indexOf("buyp_item");
    int columnSellP = rec.indexOf("sellp_item");
    int columnCity1 = rec.indexOf("stock_city1");
    int columnCity2 = rec.indexOf("stock_city2");
    int columnCity3 = rec.indexOf("stock_city3");

    mainItem_List->clear();
    mainCity_1->clear();
    mainCity_2->clear();
    mainCity_3->clear();
    while (queryDB.next())
    {
      mainItem_List->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnStock).toInt(), queryDB.value(columnBuyP).toDouble(), queryDB.value(columnSellP).toDouble(), "", queryDB.value(columnID).toInt()));
      mainCity_1->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity1).toInt(), queryDB.value(columnSellP).toDouble(), queryDB.value(columnID).toInt()));
      mainCity_2->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity2).toInt(), queryDB.value(columnSellP).toDouble(), queryDB.value(columnID).toInt()));
      mainCity_3->push_back(Item(queryDB.value(columnName).toString(), queryDB.value(columnCity3).toInt(), queryDB.value(columnSellP).toDouble(), queryDB.value(columnID).toInt()));
    }
    currentTable = tableName;

    // LOAD GRAPH VALUE
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName + "$graph$"));
    rec = queryDB.record();

    int columnSell = rec.indexOf("sellvolume_graph");
    int columnBank = rec.indexOf("bank_graph");
    int columnTax = rec.indexOf("tax_graph");
    int columnProd = rec.indexOf("prd_graph");

    sellEvo.clear();
    bankEvo.clear();
    taxEvo.clear();
    productionEvo.clear();

    while (queryDB.next())
    {
      sellEvo.push_back(queryDB.value(columnSell).toDouble());
      bankEvo.push_back(queryDB.value(columnBank).toDouble());
      taxEvo.push_back(queryDB.value(columnTax).toDouble());
      productionEvo.push_back(queryDB.value(columnProd).toDouble());
    }

    // LOAD BANK
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName + "$bank$"));
    rec = queryDB.record();
    queryDB.next();
    bank = queryDB.value(rec.indexOf("banque_data")).toDouble();

    // LOAD FACTORY
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName + "$factory$"));
    rec = queryDB.record();
    int columnFactoryLevel = rec.indexOf("level_factory");
    int columnUpgrade = rec.indexOf("upgrade_factory");

    factoryLevel_upgrade.clear();
    while (queryDB.next())
    {
      factoryLevel_upgrade.push_back({queryDB.value(columnFactoryLevel).toInt(), queryDB.value(columnUpgrade).toInt()});
    }

    // LOAD EMPLOYE
    queryDB.exec(QString("SELECT * FROM %1;").arg(tableName + "$employe$"));
    rec = queryDB.record();

    int columnNameE = rec.indexOf("name_employe");
    int columnSalaryE = rec.indexOf("salary_employe");
    int columnLevelE = rec.indexOf("level_employe");
    int columnCommercial = rec.indexOf("commercial_employe");

    employeList.clear();
    bool isCommercial = false;
    while (queryDB.next())
    {
      if (queryDB.value(columnCommercial).toInt() == 1)
      {
        isCommercial = true;
      }
      employeList.push_back(new DragEmployee(queryDB.value(columnNameE).toString(), queryDB.value(columnSalaryE).toInt(), queryDB.value(columnLevelE).toInt(), isCommercial));
      isCommercial = false;
    }
    db.close();
  }
}

QStringList ItemDAO::getTablesList()
{
  if (db.open())
  {
    QStringList tableList = db.tables();

    int sizeList = (int)tableList.size();
    for (int i = 0; i < sizeList; i++)
    {
      if (tableList.at(i).endsWith("$graph$"))
      {
        tableList.erase(tableList.begin() + i);
        i--;
        sizeList--;
      }
      else if (tableList.at(i).endsWith("$bank$"))
      {
        tableList.erase(tableList.begin() + i);
        i--;
        sizeList--;
      }
      else if (tableList.at(i).endsWith("$factory$"))
      {
        tableList.erase(tableList.begin() + i);
        i--;
        sizeList--;
      }
      else if (tableList.at(i).endsWith("$employe$"))
      {
        tableList.erase(tableList.begin() + i);
        i--;
        sizeList--;
      }
    }
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

    //Items
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
    }

    //Graph
    queryDB.exec(QString("TRUNCATE TABLE %1;").arg(currentTable + "$graph$"));

    sizeList = (int)sellEvo.size();
    for (int i = 0; i < sizeList; i++)
    {
      queryDB.prepare(QString("INSERT INTO %1 VALUES(?,?,?,?);").arg(currentTable + "$graph$"));
      queryDB.bindValue(0, sellEvo.at(i));
      queryDB.bindValue(1, bankEvo.at(i));
      queryDB.bindValue(2, taxEvo.at(i));
      queryDB.bindValue(3, productionEvo.at(i));
      queryDB.exec();
    }

    //Bank
    queryDB.exec(QString("UPDATE %1 SET banque_data = %2;").arg(currentTable + "$bank$").arg(bank));

    //Factory
    queryDB.exec(QString("TRUNCATE TABLE %1;").arg(currentTable + "$factory$"));
    sizeList = (int)factoryLevel_upgrade.size();
    for (int i = 0; i < sizeList; i++)
    {
      queryDB.prepare(QString("INSERT INTO %1 VALUES(?,?);").arg(currentTable + "$factory$"));
      queryDB.bindValue(0, factoryLevel_upgrade.at(i).first);
      queryDB.bindValue(1, factoryLevel_upgrade.at(i).second);
      queryDB.exec();
    }
    //Employe
    queryDB.exec(QString("TRUNCATE TABLE %1;").arg(currentTable + "$employe$"));
    sizeList = (int)employeList.size();
    for (int i = 0; i < sizeList; i++)
    {
      queryDB.prepare(QString("INSERT INTO %1 VALUES(?,?,?,?);").arg(currentTable + "$employe$"));
      queryDB.bindValue(0, employeList.at(i)->getName());
      queryDB.bindValue(1, employeList.at(i)->getSalary());
      queryDB.bindValue(2, employeList.at(i)->getLvl());
      queryDB.bindValue(3, QString::number(employeList.at(i)->getIsCommercial()));
      queryDB.exec();
    }
  }
  db.close();
}

void ItemDAO::itemListPushToDB(std::vector<Item>* itemList, std::vector<Item>* itemCity1, std::vector<Item>* itemCity2, std::vector<Item>* itemCity3)
{
  mainItem_List = itemList;
  mainCity_1 = itemCity1;
  mainCity_2 = itemCity2;
  mainCity_3 = itemCity3;
}

void ItemDAO::pushGrapgData(std::vector<double> newSellEvo, std::vector<double> newBankEvo, std::vector<double> newTaxEvo, std::vector<double> newProdEvo)
{
  sellEvo = newSellEvo;
  bankEvo = newBankEvo;
  taxEvo = newTaxEvo;
  productionEvo = newProdEvo;
}

void ItemDAO::bankPushToDB(double newBank)
{
  bank = newBank;
}

void ItemDAO::pushFactory(std::vector<std::pair<int, int>> newList)
{
  factoryLevel_upgrade = newList;
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
                       "id_item INT UNSIGNED AUTO_INCREMENT, "
                       "name_item TEXT, "
                       "stock_item DOUBLE(10, 3) DEFAULT '0', "
                       "buyp_item DOUBLE(10, 3), "
                       "sellp_item DOUBLE(10, 3), "

                       "stock_city1 DOUBLE(10, 3) DEFAULT '0', "
                       "stock_city2 DOUBLE(10, 3) DEFAULT '0', "
                       "stock_city3 DOUBLE(10, 3) DEFAULT '0', "
                       "PRIMARY KEY(id_item) "
                       ");")
                 .arg(name));

  queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
                       "sellvolume_graph DOUBLE(10, 3) NOT NULL, "
                       "bank_graph DOUBLE(10, 3) NOT NULL, "
                       "tax_graph DOUBLE(10, 3) NOT NULL, "
                       "prd_graph DOUBLE(10, 3) NOT NULL "
                       ");")
                 .arg(name + "$graph$"));

  queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
                       "password_table TEXT, "
                       "banque_data DOUBLE(10, 3) "
                       ");")
                 .arg(name + "$bank$"));

  queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
                       "level_factory INT NOT NULL, "
                       "upgrade_factory INT NOT NULL "
                       ");")
                 .arg(name + "$factory$"));

  queryDB.exec(QString("CREATE TABLE IF NOT EXISTS %1( "
                       "name_employe TEXT NOT NULL, "
                       "salary_employe INT NOT NULL, "
                       "level_employe INT NOT NULL, "
                       "commercial_employe INT NOT NULL "
                       ");")
                 .arg(name + "$employe$"));

  queryDB.exec(QString("INSERT INTO %1 (id_item, name_item, buyp_item, sellp_item) VALUES(NULL, 'Mug','8','31.12');").arg(name));
  queryDB.exec(QString("INSERT INTO %1 (id_item, name_item, buyp_item, sellp_item) VALUES(NULL, 'Pot','15','58.35');").arg(name));
  queryDB.exec(QString("INSERT INTO %1 (id_item, name_item, buyp_item, sellp_item) VALUES(NULL, 'Flower','2.12','8.24');").arg(name));

  queryDB.exec(QString("INSERT INTO %1 VALUES('%2','5432');").arg(name + "$bank$").arg(password));

  queryDB.exec(QString("INSERT INTO %1 VALUES('1', '750');").arg(name + "$factory$"));
  queryDB.exec(QString("INSERT INTO %1 VALUES('0', '670');").arg(name + "$factory$"));
  queryDB.exec(QString("INSERT INTO %1 VALUES('0', '780');").arg(name + "$factory$"));

  lockedList.insert({name, false});
  db.close();
}

void ItemDAO::deleteTable(QString tableName)
{
  db.open();
  QSqlQuery queryDB(db);
  queryDB.exec(QString("DROP TABLE %1").arg(tableName));
  queryDB.exec(QString("DROP TABLE %1").arg(tableName + "$graph$"));
  queryDB.exec(QString("DROP TABLE %1").arg(tableName + "$bank$"));
  queryDB.exec(QString("DROP TABLE %1").arg(tableName + "$factory$"));
  queryDB.exec(QString("DROP TABLE %1").arg(tableName + "$employe$"));
  db.close();
}

std::vector<Item>* ItemDAO::getItemList()
{
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
    default:
      return mainCity_1;
  }
}

std::vector<double> ItemDAO::getGraphData(int idGraph)
{
  switch (idGraph)
  {
    case 0:
      return sellEvo;
    case 1:
      return bankEvo;
    case 2:
      return taxEvo;
    case 3:
      return productionEvo;
    default:
      return sellEvo;
  }
}

std::vector<std::pair<int, int>> ItemDAO::getFactory()
{
  return factoryLevel_upgrade;
}

double ItemDAO::getBank()
{
  return bank;
}

std::vector<DragEmployee*> ItemDAO::getEmployeList()
{
  return employeList;
}

QString ItemDAO::getCurrentTable()
{
  return currentTable;
}

void ItemDAO::loadPassword()
{
  QStringList listTable = getTablesList();
  int tableSize = (int)listTable.size();

  db.open();
  QSqlQuery queryDB(db);
  QSqlRecord rec;

  for (int i = 0; i < tableSize; i++)
  {
    queryDB.exec(QString("SELECT * FROM %1;").arg(listTable.at(i) + "$bank$"));

    rec = queryDB.record();
    int columnID = rec.indexOf("password_table");

    queryDB.next();
    passwordList.insert({listTable.at(i), queryDB.value(columnID).toString()});
  }
  db.close();

  for (int i = 0; i < tableSize; i++)
  {
    if (passwordList.at(listTable.at(i)) != "")
    {
      lockedList.insert({listTable.at(i), true});
    }
    else
    {
      lockedList.insert({listTable.at(i), false});
    }
  }
}

bool ItemDAO::isLocked(QString tableName)
{
  return lockedList.at(tableName);
}

QString ItemDAO::getPassword(QString tableName)
{
  return passwordList.at(tableName);
}

void ItemDAO::isUnlocked(QString tableName)
{
  lockedList.at(tableName) = false;
}

void ItemDAO::addItemToTable(QString table, QString name, double buyP, double sellP)
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

void ItemDAO::pushEmployee(std::vector<DragEmployee*> employe, std::vector<DragEmployee*> commercial)
{
  //(employeList.begin(), employeList.end());
  employeList.clear();

  int sizeList = (int)employe.size();
  for (int i = 0; i < sizeList; i++)
  {
    employeList.push_back(employe.at(i));
  }

  sizeList = (int)commercial.size();
  for (int i = 0; i < sizeList; i++)
  {
    employeList.push_back(commercial.at(i));
  }
}