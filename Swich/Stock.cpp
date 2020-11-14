#include "Stock.h"

Stock::Stock(std::vector<Item>& getItemList)
{
  listItem = &getItemList;
  setStock();
}

void Stock::setStock()
{
  QVBoxLayout* layoutStock = new QVBoxLayout(this);

  tab = new QTableWidget((int)listItem->size(), 7, this);
  QStringList columnName;
  columnName << tr("View") << tr("Name") << tr("Stock") << tr("SellP.") << tr("BuyP.") << tr("City's Stocks") << tr("Monthly Sells");
  tab->setHorizontalHeaderLabels(columnName);

  textDefault = new QLabel(tr("Commercial might be helpfull."), this);

  //Inactivate Commercial
  commercialWidget = new QWidget(this);
  QGridLayout* layoutCommercial = new QGridLayout(this);
  pictureId = new QLabel(this);
  name = new QLabel(this);
  salary = new QLabel(this);
  displayPushedItems = new QLabel(this);
  QLabel* textPushedItems = new QLabel(tr("Items pushed"), this);
  QCheckBox* buttonRadio = new QCheckBox(this);

  commercialWidget->setLayout(layoutCommercial);
  layoutCommercial->addWidget(pictureId, 0, 0);
  layoutCommercial->addWidget(name, 0, 1);
  layoutCommercial->addWidget(salary, 0, 2);
  layoutCommercial->addWidget(displayPushedItems, 0, 3);
  layoutCommercial->addWidget(textPushedItems, 0, 4);
  layoutCommercial->addWidget(buttonRadio, 0, 5);
  commercialWidget->setVisible(false);

  this->setLayout(layoutStock);
  layoutStock->addWidget(tab);
  layoutStock->addWidget(textDefault);
  layoutStock->addWidget(commercialWidget);

  commercialWidget->setObjectName("widget");
  setList();
  tab->resizeColumnsToContents();
  connect(buttonRadio, SIGNAL(stateChanged(int)), this, SLOT(updateRadioButton(int)));
}

void Stock::setList()
{
  int sizeInventory = (int)listItem->size();
  tab->setSortingEnabled(false);
  tab->clearContents();
  tab->setRowCount(sizeInventory);

  int y = 0;

  for (int i = 0; i < sizeInventory; i++)
  {
    y = 0;
    QLabel* pixItem = new QLabel(this);
    QTableWidgetItem* nameItem = new QTableWidgetItem(listItem->at(i).getNom());
    QTableWidgetItem* stockItem = new QTableWidgetItem(QString::number(listItem->at(i).getRoundedStock()));
    QTableWidgetItem* buyPItem = new QTableWidgetItem(QString::number(listItem->at(i).getBuyP()));
    QTableWidgetItem* sellPItem = new QTableWidgetItem(QString::number(listItem->at(i).getSellP()));
    QTableWidgetItem* cityStockItem = new QTableWidgetItem(QString::number(listItem->at(i).getRoundedStock()));
    QTableWidgetItem* mounthlySellItem = new QTableWidgetItem(QString::number(listItem->at(i).getAveSell()));

    nameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    stockItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    buyPItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    sellPItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    cityStockItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    mounthlySellItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QPixmap pix(listItem->at(i).getPix());
    pix = pix.scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixItem->setPixmap(pix);

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

void Stock::updateStock()
{

  tab->setSortingEnabled(false);
  tab->sortItems(1, Qt::AscendingOrder);

  for (int i = 0; i < listItem->size(); i++)
  {
    QTableWidgetItem* stockItem = new QTableWidgetItem(QString::number(listItem->at(i).getRoundedStock()));

    stockItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    tab->setItem(i, 2, stockItem);
  }
  tab->setSortingEnabled(true);
}

void Stock::updateCommercialSlot(DragEmployee* getEmploye)
{
  commercialWidget->setVisible(true);

  SingleData* single = single->getInstance();
  pictureId->setPixmap(single->getPixmap(getEmploye->getName()));
  name->setText(getEmploye->getName());
  salary->setText(QString::number(getEmploye->getSalary()));

  textDefault->setVisible(false);
}

void Stock::firedCommercial()
{
  commercialWidget->setVisible(false);
  textDefault->setVisible(true);
}

void Stock::updateRadioButton(int position)
{
  if (position == 2)
  {
    commercialWidget->setStyleSheet("QWidget#widget {border: 3px solid #ffd740;}");
    emit setIsActivated(true);
  }
  else
  {
    commercialWidget->setStyleSheet("QWidget#widget {border: 3px solid #262626;}");
    emit setIsActivated(false);
  }
}