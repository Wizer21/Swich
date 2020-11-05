#include "Sell.h"

Sell::Sell(std::vector<Item>& item, std::vector<City>& city)
{
  getItemList = &item;
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

  this->setLayout(layoutSell);

  layoutSell->addWidget(scrollArea, 0, 0);
  scrollArea->setWidget(widArea);
  widArea->setLayout(layoutArea);

  layoutArea->setAlignment(Qt::AlignTop);
  scrollArea->setWidgetResizable(true);
  setList(layoutArea);

  layoutSell->addWidget(tabWidget, 0, 1);
  setCity(tabWidget);
}

void Sell::setList(QVBoxLayout* layout)
{
  for (int i = 0; i < getItemList->size(); i++)
  {
    Dragwidget* widgetContainer = new Dragwidget(this, getItemList->at(i).getNom(), 0, getItemList->at(i).getId());
    QGridLayout* layoutGrid = new QGridLayout(this);
    QLabel* titre = new QLabel(getItemList->at(i).getNom(), this);
    QLineEdit* stock = new QLineEdit(QString::number(getItemList->at(i).getStock()), this);
    QSlider* slider = new QSlider(Qt::Horizontal, this);

    widgetContainer->setObjectName(QString::number(id));
    stock->setObjectName(QString::number(id));
    slider->setObjectName(QString::number(id++));
    slider->setMaximum(getItemList->at(i).getStock());

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
  getLine->setText(QString::number(getItemList->at(sender()->objectName().toInt()).getStock() - value));
  getWidget->setVolume(value);
}

void Sell::dynamicStockId(int value, int id)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(id));
  Dragwidget* getWidget = this->findChild<Dragwidget*>(QString::number(id));
  getLine->setText(QString::number(getItemList->at(QString::number(id).toInt()).getStock()));
  getWidget->setVolume(value);
}

void Sell::setCity(QTabWidget* tab)
{
  for (int i = 0; i < getCityList->size(); i++)
  {
    QWidget* widgetCity = new QWidget(this);
    QGridLayout* layoutCity = new QGridLayout(this);

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
    layoutCity->addWidget(scrollArea, 0, 0, 2, 1);
    layoutCity->addWidget(tabCity, 0, 1, 1, 2);
    scrollArea->setWidget(widgetArea);
    widgetArea->setLayout(layoutWidget);

    layoutWidget->setAlignment(Qt::AlignTop);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumWidth(this->width() * 0.3);

    tabCity->setObjectName(QString::number(i));
    layoutWidget->setObjectName(QString::number(i));
    connect(scrollArea, SIGNAL(transfertData(QString, QString, int)), this, SLOT(setNewItem(QString, QString, int)));
  }
}

void Sell::setNewItem(QString nom, QString vol, int id)
{
  if (this->findChild<QWidget*>(QString::number(id) + "d"))
  {
    QLineEdit* getLine = this->findChild<QLineEdit*>(QString::number(id) + "d");
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
    volDragged->setObjectName(QString::number(id) + "d");
    draggedItem->setObjectName(QString::number(id) + "d");
    kill->setObjectName(QString::number(id) + "d");

    connect(kill, SIGNAL(clicked()), this, SLOT(cancelSell()));
  }
  QSlider* getSlider = this->findChild<QSlider*>(QString::number(id));
  getSlider->setMaximum(getSlider->maximum() - vol.toInt());
  getSlider->setValue(0);
  getItemList->at(id).setStock(getItemList->at(id).getStock() - vol.toInt());

  dynamicStockId(vol.toInt(), id);

  updateCityOnDrop(vol, id);
}

void Sell::updateCityOnDrop(QString vol, int idItem)
{
  QTableWidget* getTable = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  getCityList->at(tabWidget->currentIndex()).addToList(Item(getItemList->at(idItem).getNom(), vol.toInt(), getItemList->at(idItem).getSellP(), getItemList->at(idItem).getId()));
  setTabCity(getTable, getCityList->at(tabWidget->currentIndex()).getList());
}

void Sell::cancelSell()
{
  QWidget* getWidget = this->findChild<QWidget*>(sender()->objectName());
  QLineEdit* getVol = this->findChild<QLineEdit*>(sender()->objectName());
  QString id = (sender()->objectName().at(0));
  QSlider* getSlider = this->findChild<QSlider*>(id);

  getItemList->at(id.toInt()).setStock(getItemList->at(id.toInt()).getStock() + getVol->text().toInt());
  getSlider->setMaximum(getItemList->at(id.toInt()).getStock());

  //Tableau
  QTableWidget* tableWidget = this->findChild<QTableWidget*>(QString::number(tabWidget->currentIndex()));
  getCityList->at(tabWidget->currentIndex()).removeStock(id.toInt(), getVol->text().toInt());

  setTabCity(tableWidget, getCityList->at(tabWidget->currentIndex()).getList());

  delete getWidget;
  getWidget = nullptr;
  dynamicStockId(0, id.toInt());
}

void Sell::setTabCity(QTableWidget* tab, std::vector<Item> list)
{
  tab->setSortingEnabled(false);
  tab->clearContents();
  tab->setRowCount(list.size());
  for (int i = 0; i < list.size(); i++)
  {
    QTableWidgetItem* nameItem = new QTableWidgetItem(list.at(i).getNom());
    QTableWidgetItem* stockItem = new QTableWidgetItem(QString::number(list.at(i).getStock()));

    tab->setItem(i, 0, nameItem);
    tab->setItem(i, 1, stockItem);
  }
  tab->setSortingEnabled(true);
}