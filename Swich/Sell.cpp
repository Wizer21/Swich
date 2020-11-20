#include "Sell.h"

Sell::Sell(std::vector<City>& city)
{
  getCityList = &city;
  id = 0;
  setSell();
}

void Sell::setSell()
{
  QGridLayout* layoutSell = new QGridLayout(this);

  QScrollArea* scrollArea = new QScrollArea(this);
  QWidget* widArea = new QWidget(this);
  QVBoxLayout* layoutArea = new QVBoxLayout(this);

  tabWidget = new QTabWidget(this);

  QPushButton* validSend = new QPushButton(tr("Validate all"), this);

  this->setLayout(layoutSell);

  layoutSell->addWidget(scrollArea, 0, 0, 2, 1);
  scrollArea->setWidget(widArea);
  widArea->setLayout(layoutArea);

  layoutArea->setAlignment(Qt::AlignTop);
  scrollArea->setWidgetResizable(true);
  setList(layoutArea);

  layoutSell->addWidget(tabWidget, 0, 1);
  setCity(tabWidget);

  layoutSell->addWidget(validSend, 1, 1);

  validSend->setCursor(Qt::PointingHandCursor);
  tabWidget->tabBar()->setCursor(Qt::PointingHandCursor);
  connect(validSend, SIGNAL(clicked()), this, SLOT(validate()));
}

void Sell::setList(QVBoxLayout* layout)
{
  std::vector<Item>* itemList = ItemDAO::getInstance()->getItemList();
  int sizeList = (int)itemList->size();
  for (int i = 0; i < sizeList; i++)
  {
    Dragwidget* widgetContainer = new Dragwidget(this, itemList->at(i).getNom(), 0, itemList->at(i).getId());
    QGridLayout* layoutGrid = new QGridLayout(this);
    QLabel* titre = new QLabel(itemList->at(i).getNom(), this);
    QLineEdit* stock = new QLineEdit(QString::number(itemList->at(i).getRoundedStock()), this);
    Jumpslider* slider = new Jumpslider(Qt::Horizontal, this);

    widgetContainer->setObjectName(QString::number(id));
    stock->setObjectName(QString::number(id));
    slider->setObjectName(QString::number(id++));
    slider->setMaximum(itemList->at(i).getRoundedStock());

    layout->addWidget(widgetContainer);
    widgetContainer->setLayout(layoutGrid);
    layoutGrid->addWidget(titre, 0, 0);
    layoutGrid->addWidget(stock, 0, 1);
    layoutGrid->addWidget(slider, 1, 0, 1, 2);

    slider->setPageStep(1);
    stock->setAcceptDrops(false);
    stock->setDisabled(true);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(dynamicStockSender(int)));
  }
}

void Sell::dynamicStockSender(int value)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(sender()->objectName());
  Dragwidget* getWidget = this->findChild<Dragwidget*>(sender()->objectName());
  getLine->setText(QString::number(ItemDAO::getInstance()->getItemList()->at(sender()->objectName().toInt()).getRoundedStock() - value));
  getWidget->setVolume(value);
}

void Sell::dynamicStockId(int idStock)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(idStock));
  Dragwidget* getWidget = this->findChild<Dragwidget*>(QString::number(idStock));
  getLine->setText(QString::number(ItemDAO::getInstance()->getItemList()->at(idStock).getRoundedStock()));
  getWidget->setVolume(0);
}

void Sell::setCity(QTabWidget* tab)
{
  int citySize = (int)getCityList->size();
  for (int i = 0; i < citySize; i++)
  {
    QWidget* widgetCity = new QWidget(this);
    QGridLayout* layoutCity = new QGridLayout(this);

    QSplitter* split = new QSplitter(Qt::Horizontal, this);
    //Scroll
    DropWidget* scrollArea = new DropWidget(this);
    QWidget* widgetArea = new QWidget(this);
    QVBoxLayout* layoutWidget = new QVBoxLayout(this);

    //Tab
    QTableWidget* tabCity = new QTableWidget(0, 2, this);
    QStringList columnName;
    columnName << tr("Name") << tr("Stock");

    tabCity->setHorizontalHeaderLabels(columnName);
    tabCity->setSortingEnabled(true);
    tabCity->resizeColumnsToContents();
    setTabCity(tabCity, getCityList->at(i).getList());

    tab->addTab(widgetCity, getCityList->at(i).getNom());
    widgetCity->setLayout(layoutCity);
    layoutCity->addWidget(split, 0, 0);
    split->addWidget(scrollArea);
    split->addWidget(tabCity);
    scrollArea->setWidget(widgetArea);
    widgetArea->setLayout(layoutWidget);

    scrollArea->setMinimumWidth(10);
    split->setCollapsible(0, false);
    split->setCollapsible(1, false);
    split->show();
    layoutWidget->setAlignment(Qt::AlignTop);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(this->width() * 0.3);

    tabCity->setMinimumWidth(150);
    tabCity->setObjectName(QString::number(i));
    layoutWidget->setObjectName(QString::number(i));
    connect(scrollArea, SIGNAL(transfertData(QString, QString, int)), this, SLOT(setNewItem(QString, QString, int)));
  }
}

void Sell::setNewItem(QString nom, QString vol, int newId)
{
  QString pos = QString("%1d%2").arg(newId).arg(tabWidget->currentIndex());
  if (this->findChild<QWidget*>(pos))
  {
    QLineEdit* getLine = this->findChild<QLineEdit*>(pos);
    QString stockStock = getLine->text();
    getLine->setText(QString::number(stockStock.toInt() + vol.toInt()));
  }
  else
  {
    QVBoxLayout* getZone = this->findChild<QVBoxLayout*>(QString::number(tabWidget->currentIndex()));
    QWidget* draggedItem = new QWidget(this);
    QHBoxLayout* layoutItem = new QHBoxLayout(this);
    QLabel* nomDragged = new QLabel(nom, this);
    QLineEdit* volDragged = new QLineEdit(vol, this);
    QPushButton* kill = new QPushButton("X", this);

    getZone->addWidget(draggedItem);
    draggedItem->setLayout(layoutItem);
    layoutItem->addWidget(nomDragged);
    layoutItem->addWidget(volDragged);
    layoutItem->addWidget(kill);

    volDragged->setDisabled(true);
    volDragged->setAcceptDrops(false);
    volDragged->isReadOnly();
    volDragged->setObjectName(pos);
    draggedItem->setObjectName(pos);
    kill->setObjectName(pos);
    widgetToDelete.push_back(draggedItem);

    kill->setCursor(Qt::PointingHandCursor);
    connect(kill, SIGNAL(clicked()), this, SLOT(cancelSell()));
  }
  QSlider* getSlider = this->findChild<QSlider*>(QString::number(newId));
  getSlider->setMaximum(getSlider->maximum() - vol.toInt());
  getSlider->setValue(0);
  ItemDAO::getInstance()->getItemList()->at(newId).setStock(ItemDAO::getInstance()->getItemList()->at(newId).getStock() - vol.toInt());

  dynamicStockId(newId);

  updateCityOnDrop(vol, newId);
}

void Sell::updateCityOnDrop(QString vol, int idItem)
{
  QTableWidget* getTable = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  Item getItem = ItemDAO::getInstance()->getItemList()->at(idItem);
  getCityList->at(tabWidget->currentIndex()).addToList(Item(getItem.getNom(), vol.toInt(), getItem.getSellP(), getItem.getId()));
  setTabCity(getTable, getCityList->at(tabWidget->currentIndex()).getList());
}

void Sell::cancelSell()
{
  QWidget* getWidget = this->findChild<QWidget*>(sender()->objectName());
  QLineEdit* getVol = this->findChild<QLineEdit*>(sender()->objectName());
  QString idStr = (sender()->objectName().at(0));
  QSlider* getSlider = this->findChild<QSlider*>(idStr);

  ItemDAO::getInstance()->getItemList()->at(idStr.toInt()).setStock(ItemDAO::getInstance()->getItemList()->at(idStr.toInt()).getStock() + getVol->text().toInt());
  getSlider->setMaximum(ItemDAO::getInstance()->getItemList()->at(idStr.toInt()).getRoundedStock());

  //Tableau
  QTableWidget* tableWidget = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  getCityList->at(tabWidget->currentIndex()).removeStock(idStr.toInt(), getVol->text().toInt());

  setTabCity(tableWidget, getCityList->at(tabWidget->currentIndex()).getList());

  for (int i = 0; i < widgetToDelete.size(); i++)
  {
    if (widgetToDelete.at(i) == getWidget)
    {
      widgetToDelete.erase(widgetToDelete.begin() + i);
      break;
    }
  }

  delete getWidget;
  getWidget = nullptr;
  dynamicStockId(idStr.toInt());
}

void Sell::setTabCity(QTableWidget* tab, std::vector<Item> list)
{
  int sizeCityList = (int)list.size();
  tab->setSortingEnabled(false);
  tab->setRowCount(sizeCityList);

  for (int i = 0; i < sizeCityList; i++)
  {
    QTableWidgetItem* nameItem = new QTableWidgetItem(list.at(i).getNom());
    QTableWidgetItem* stockItem = new QTableWidgetItem(QString::number(list.at(i).getRoundedStock()));

    nameItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    stockItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    tab->setItem(i, 0, nameItem);
    tab->setItem(i, 1, stockItem);
  }
  tab->setSortingEnabled(true);
}

void Sell::validate()
{
  int toDeleteSize = (int)widgetToDelete.size();
  for (int i = 0; i < toDeleteSize; i++)
  {
    if (widgetToDelete.at(i))
    {
      delete widgetToDelete.at(i);
      widgetToDelete.at(i) = nullptr;
    }
    widgetToDelete.erase(widgetToDelete.begin() + i);
    i--;
  }
  emit callUpdateStock();
}

void Sell::refreshStock()
{
  int citySize = (int)getCityList->size();
  for (int i = 0; i < citySize; i++)
  {
    QTableWidget* getTable = this->findChild<QTableWidget*>(QString::number(i));
    setTabCity(getTable, getCityList->at(i).getList());
  }

  std::vector<Item>* itemList = ItemDAO::getInstance()->getItemList();
  int itemSize = itemList->size();
  for (int i = 0; i < itemSize; i++)
  {
    QSlider* getSliderR = this->findChild<QSlider*>(QString::number(i));
    QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(i));
    getLine->setText(QString::number(itemList->at(i).getRoundedStock()));
    getSliderR->setMaximum(itemList->at(i).getRoundedStock());
  }
}