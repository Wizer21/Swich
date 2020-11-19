#include "ItemDAO.h"

ItemDAO::ItemDAO()
{
  mainItem_List = new std::vector<Item>();
  iniDB();
  loadDBToItemList();
}

ItemDAO* ItemDAO::instance = 0;

void ItemDAO::iniDB()
{
  QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
  database.setHostName("localhost");
  database.setDatabaseName("swichdb");
  database.setUserName("Wizer");
  database.setPassword("useraccount");

  if (database.open())
  {
    QSqlQuery queryDB(database);

    queryDB.exec("SELECT * FROM SWICHITEM;");
    QSqlRecord rec = queryDB.record();

    // Get Column ID
    int columnID = rec.indexOf("id_item");
    int columnName = rec.indexOf("name_item");
    int columnStock = rec.indexOf("stock_item");
    int columnBuyP = rec.indexOf("buyp_item");
    int columnSellP = rec.indexOf("sellp_item");

    // Push to list
    while (queryDB.next())
    {
      getData_Id.push_back(queryDB.value(columnID).toInt());
      getData_Name.push_back(queryDB.value(columnName).toString());
      getData_Stock.push_back(queryDB.value(columnStock).toInt());
      getData_BuyP.push_back(queryDB.value(columnBuyP).toInt());
      getData_SellP.push_back(queryDB.value(columnSellP).toInt());
    }
  }
  database.close();
}

void ItemDAO::loadDBToItemList()
{
  int sizeList = getData_Id.size();
  for (int i = 0; i < sizeList; i++)
  {
    mainItem_List->push_back(Item(getData_Name.at(i), getData_Stock.at(i), getData_BuyP.at(i), getData_SellP.at(i), "", getData_Id.at(i)));
  }
}

std::vector<Item>* ItemDAO::getItemList()
{
  return mainItem_List;
}
