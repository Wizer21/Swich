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
  QWidget* widgetLeft = new QWidget(this);
  QHBoxLayout* layoutLeft = new QHBoxLayout(this);
  QWidget* centralWidget = new QWidget(this);
  QHBoxLayout* layoutCentral = new QHBoxLayout(this);
  QWidget* widgetRight = new QWidget(this);
  QHBoxLayout* layoutRight = new QHBoxLayout(this);
  pictureId = new QLabel(this);
  name = new QLabel(this);
  salary = new QLabel("0", this);
  displayPushedItems = new QLabel("0", this);
  QLabel* textPushedItems = new QLabel(tr("Items pushed"), this);
  QCheckBox* buttonRadio = new QCheckBox(this);

  commercialWidget->setLayout(layoutCommercial);
  layoutCommercial->addWidget(widgetLeft, 0, 0);
  widgetLeft->setLayout(layoutLeft);
  layoutCommercial->addWidget(centralWidget, 0, 1);
  centralWidget->setLayout(layoutCentral);
  layoutCommercial->addWidget(widgetRight, 0, 2);
  widgetRight->setLayout(layoutRight);
  layoutLeft->addWidget(pictureId);
  layoutLeft->addWidget(name);
  layoutLeft->addWidget(salary);
  layoutCentral->addWidget(displayPushedItems);
  layoutCentral->addWidget(textPushedItems);
  layoutRight->addWidget(buttonRadio);
  commercialWidget->setVisible(false);
  layoutCentral->setAlignment(Qt::AlignLeft);
  layoutLeft->setAlignment(Qt::AlignLeft);
  layoutRight->setAlignment(Qt::AlignRight);

  this->setLayout(layoutStock);
  layoutStock->addWidget(tab);
  layoutStock->addWidget(textDefault);
  layoutStock->addWidget(commercialWidget);

  layoutLeft->setContentsMargins(0, 0, 0, 0);
  layoutRight->setContentsMargins(0, 0, 0, 0);
  buttonRadio->setChecked(true);
  commercialWidget->setObjectName("widget");
  setList();
  tab->resizeColumnsToContents();
  layoutStock->setAlignment(textDefault, Qt::AlignCenter);
  textDefault->setMinimumHeight(60);

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

    commercialWidget->setStyleSheet("QWidget#widget {border: 3px solid #ffd740;}");
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
  salary->setText(QString::number(getEmploye->getSalary()) + tr("$"));

  updateRadioButton(2);

  displayPushedItems->setAlignment(Qt::AlignLeft);
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
    displayPushedItems->setStyleSheet("color:#ffd740; font-size:28px;");
    salary->setStyleSheet("color:#ffd740; font-size:18px;");
    emit setIsActivated(true);
  }
  else
  {
    commercialWidget->setStyleSheet("QWidget#widget {border: 3px solid #262626;}");
    displayPushedItems->setStyleSheet("color:#262626; font-size:28px;");
    salary->setStyleSheet("color:#262626; font-size:18px;");
    emit setIsActivated(false);
  }
}

void Stock::setItemPushed(int nrbItem)
{
  displayPushedItems->setText(QString::number(nrbItem));
  displayPushedItems->setStyleSheet("color:#ffd740; font-size:28px;");
}