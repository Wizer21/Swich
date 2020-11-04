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

    stock->setAcceptDrops(false);
    stock->setDisabled(true);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(dynamicStock(int)));
  }
}

void Sell::dynamicStock(int value)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(sender()->objectName());
  Dragwidget* getWidget = this->findChild<Dragwidget*>(sender()->objectName());
  getLine->setText(QString::number(getItemList->at(sender()->objectName().toInt()).getStock() - value));
  getWidget->setVolume(value);
}

void Sell::setCity(QTabWidget* tab)
{
  for (int i = 0; i < getCityList->size(); i++)
  {
    DropWidget* scrollArea = new DropWidget(this);
    QWidget* widgetArea = new QWidget(this);
    QVBoxLayout* layoutWidget = new QVBoxLayout(this);

    scrollArea->setWidget(widgetArea);
    widgetArea->setLayout(layoutWidget);

    layoutWidget->setAlignment(Qt::AlignTop);
    scrollArea->setWidgetResizable(true);
    tab->addTab(scrollArea, getCityList->at(i).getNom());
    layoutWidget->setObjectName(QString::number(i));
    connect(scrollArea, SIGNAL(transfertData(QString, QString, int)), this, SLOT(setNewItem(QString, QString, int)));
  }
}

void Sell::setNewItem(QString nom, QString vol, int id)
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

  QSlider* getSlider = this->findChild<QSlider*>(QString::number(id));
  getSlider->setMaximum(getSlider->maximum() - vol.toInt());
  getItemList->at(id).setStock(getItemList->at(id).getStock() - vol.toInt());

  dynamicStock(vol.toInt());

  getSlider->setValue(getSlider->value() - vol.toInt());
}