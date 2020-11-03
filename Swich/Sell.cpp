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

  QTabWidget* tabWidget = new QTabWidget(this);

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
    QWidget* widgetContainer = new QWidget(this);
    QGridLayout* layoutGrid = new QGridLayout(this);
    QLabel* titre = new QLabel(getItemList->at(i).getNom(), this);
    QLineEdit* stock = new QLineEdit(QString::number(getItemList->at(i).getStock()), this);
    QSlider* slider = new QSlider(Qt::Horizontal, this);

    stock->setObjectName(QString::number(id));
    slider->setObjectName(QString::number(id++));
    slider->setMaximum(getItemList->at(i).getStock());

    layout->addWidget(widgetContainer);
    widgetContainer->setLayout(layoutGrid);
    layoutGrid->addWidget(titre, 0, 0);
    layoutGrid->addWidget(stock, 0, 1);
    layoutGrid->addWidget(slider, 1, 0, 1, 2);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(dynamicStock(int)));
  }
}

void Sell::dynamicStock(int value)
{
  QLineEdit* getLine = this->findChild<QLineEdit*>(sender()->objectName());
  getLine->setText(QString::number(getItemList->at(sender()->objectName().toInt()).getStock() - value));
}

void Sell::setCity(QTabWidget* tab)
{

  for (int i = 0; i < getCityList->size(); i++)
  {
    QWidget* widgetTab = new QWidget(this);
    tab->addTab(widgetTab, getCityList->at(i).getNom());
  }
}