#include "Stock.h"

Stock::Stock(std::vector<Item>& getItemList)
{
  listItem = &getItemList;
  setStock();
}

void Stock::setStock()
{
  QHBoxLayout* layoutStock = new QHBoxLayout(this);

  tab = new QTableWidget(listItem->size(), 7, this);
  QStringList columnName;
  columnName << tr("View") << tr("Name") << tr("Stock") << tr("SellP.") << tr("BuyP.") << tr("City's Stocks") << tr("Mounthly Sells");
  tab->setHorizontalHeaderLabels(columnName);

  this->setLayout(layoutStock);

  layoutStock->addWidget(tab, 0, 0);

  setList();
  tab->resizeColumnsToContents();
}

void Stock::setList()
{

  tab->setSortingEnabled(false);
  tab->clearContents();
  tab->setRowCount(listItem->size());

  int y = 0;

  for (int i = 0; i < listItem->size(); i++)
  {
    y = 0;
    QLabel* pixItem = new QLabel(this);
    QTableWidgetItem* nameItem = new QTableWidgetItem(listItem->at(i).getNom());
    QTableWidgetItem* stockItem = new QTableWidgetItem(QString::number(listItem->at(i).getRoundedStock()));
    QTableWidgetItem* buyPItem = new QTableWidgetItem(QString::number(listItem->at(i).getBuyP()));
    QTableWidgetItem* sellPItem = new QTableWidgetItem(QString::number(listItem->at(i).getSellP()));
    QTableWidgetItem* cityStockItem = new QTableWidgetItem(QString::number(listItem->at(i).getRoundedStock()));
    QTableWidgetItem* mounthlySellItem = new QTableWidgetItem(QString::number(listItem->at(i).getAveSell()));

    tab->setCellWidget(i, y++, pixItem);
    tab->setItem(i, y++, nameItem);
    tab->setItem(i, y++, stockItem);
    tab->setItem(i, y++, buyPItem);
    tab->setItem(i, y++, sellPItem);
    tab->setItem(i, y++, cityStockItem);
    tab->setItem(i, y++, mounthlySellItem);
  }
  tab->setSortingEnabled(true);
}