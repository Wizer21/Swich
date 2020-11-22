#include "Sell.h"

Sell::Sell(std::vector<City>& city, std::vector<Item>* getListItem)
{
  getCityList = &city;
  getList = getListItem;
  setSell();
}

void Sell::setSell()
{
  QGridLayout* layoutSell = new QGridLayout(this);

  QScrollArea* scrollArea = new QScrollArea(this);
  QWidget* widArea = new QWidget(this);
  layoutArea = new QVBoxLayout(this);

  tabWidget = new QTabWidget(this);

  QPushButton* validSend = new QPushButton(tr("Validate all"), this);

  this->setLayout(layoutSell);

  layoutSell->addWidget(scrollArea, 0, 0, 2, 1);
  scrollArea->setWidget(widArea);
  widArea->setLayout(layoutArea);

  layoutArea->setAlignment(Qt::AlignTop);
  scrollArea->setWidgetResizable(true);
  setList();

  layoutSell->addWidget(tabWidget, 0, 1);
  setCity(tabWidget);

  layoutSell->addWidget(validSend, 1, 1);

  validSend->setCursor(Qt::PointingHandCursor);
  tabWidget->tabBar()->setCursor(Qt::PointingHandCursor);
  connect(validSend, SIGNAL(clicked()), this, SLOT(validate()));
}

void Sell::setList()
{
  qDeleteAll(widgetFromItemList.begin(), widgetFromItemList.end());
  widgetFromItemList.clear();

  int sizeList = (int)getList->size();
  for (int i = 0; i < sizeList; i++)
  {
    Dragwidget* widgetContainer = new Dragwidget(this, getList->at(i).getNom(), 0, getList->at(i).getId());
    QGridLayout* layoutGrid = new QGridLayout(this);
    QLabel* titre = new QLabel(getList->at(i).getNom(), this);
    QLineEdit* stock = new QLineEdit(QString::number(getList->at(i).getRoundedStock()), this);
    QSlider* slider = new QSlider(Qt::Horizontal, this);

    widgetContainer->setObjectName(QString::number(i));
    stock->setObjectName(QString::number(i));
    slider->setObjectName(QString::number(i));
    slider->setMaximum(getList->at(i).getRoundedStock());
    sliderList.insert({getList->at(i).getId(), slider});

    layoutArea->addWidget(widgetContainer);
    widgetContainer->setLayout(layoutGrid);
    layoutGrid->addWidget(titre, 0, 0);
    layoutGrid->addWidget(stock, 0, 1);
    layoutGrid->addWidget(slider, 1, 0, 1, 2);

    slider->setPageStep(1);
    stock->setAcceptDrops(false);
    stock->setDisabled(true);

    widgetFromItemList.push_back(widgetContainer);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(dynamicStockSender(int)));
  }
}

void Sell::dynamicStockSender(int value)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(sender()->objectName());
  Dragwidget* getWidget = this->findChild<Dragwidget*>(sender()->objectName());
  getLine->setText(QString::number(getList->at(sender()->objectName().toInt()).getRoundedStock() - value));
  getWidget->setVolume(value);
}

void Sell::dynamicStockId(int idStock)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(idStock));
  Dragwidget* getWidget = this->findChild<Dragwidget*>(QString::number(idStock));
  getLine->setText(QString::number(getList->at(idStock).getRoundedStock()));
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
  QString pos = QString("%1$%2").arg(newId).arg(tabWidget->currentIndex());
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
  sliderList.at(newId)->setMaximum(sliderList.at(newId)->maximum() - vol.toInt());
  sliderList.at(newId)->setValue(0);

  int sizeItemList = (int)getList->size();
  for (int i = 0; i < sizeItemList; i++)
  {
    if (getList->at(i).getId() == newId)
    {
      getList->at(i).setStock(getList->at(i).getStock() - vol.toInt());
      dynamicStockId(i);
      updateCityOnDrop(vol, i);
      break;
    }
  }
}

void Sell::updateCityOnDrop(QString vol, int idPos)
{
  QTableWidget* getTable = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  Item getItem = getList->at(idPos);
  getCityList->at(tabWidget->currentIndex()).addToList(Item(getItem.getNom(), vol.toInt(), getItem.getSellP(), getItem.getId()));
  setTabCity(getTable, getCityList->at(tabWidget->currentIndex()).getList());
}

void Sell::cancelSell()
{
  QWidget* getWidget = this->findChild<QWidget*>(sender()->objectName());
  QLineEdit* getVol = this->findChild<QLineEdit*>(sender()->objectName());
  QStringList idStr = (sender()->objectName().split("$"));

  int posFromItemList = 0;
  int sizeItemList = (int)getList->size();
  for (int i = 0; i < sizeItemList; i++)
  {
    if (getList->at(i).getId() == idStr.at(0).toInt())
    {
      posFromItemList = i;
      break;
    }
  }

  getList->at(posFromItemList).setStock(getList->at(posFromItemList).getStock() + getVol->text().toInt());
  sliderList.at(idStr.at(0).toInt())->setMaximum(getList->at(posFromItemList).getRoundedStock());

  //Tableau
  QTableWidget* tableWidget = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  getCityList->at(tabWidget->currentIndex()).removeStock(idStr.at(0).toInt(), getVol->text().toInt());

  setTabCity(tableWidget, getCityList->at(tabWidget->currentIndex()).getList());

  int toDeleteSize = widgetToDelete.size();
  for (int i = 0; i < toDeleteSize; i++)
  {
    if (widgetToDelete.at(i) == getWidget)
    {
      widgetToDelete.erase(widgetToDelete.begin() + i);
      break;
    }
  }

  delete getWidget;
  getWidget = nullptr;
  dynamicStockId(posFromItemList);
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

  int itemSize = (int)getList->size();
  for (int i = 0; i < itemSize; i++)
  {
    QSlider* getSliderR = this->findChild<QSlider*>(QString::number(i));
    QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(i));
    getLine->setText(QString::number(getList->at(i).getRoundedStock()));
    getSliderR->setMaximum(getList->at(i).getRoundedStock());
  }
}