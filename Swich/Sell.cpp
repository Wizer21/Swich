#include "Sell.h"

Sell::Sell()
{
  setSell();
}

void Sell::setSell()
{

  QGridLayout* layoutSell = new QGridLayout(this);

  QWidget* widgetMenuLeft = new QWidget(this);
  QVBoxLayout* widgetList = new QVBoxLayout(this);
  QPushButton* sellButton = new QPushButton(tr("Sell"), this);

  this->setLayout(layoutSell);

  layoutSell->addWidget(widgetMenuLeft, 0, 0);
  widgetMenuLeft->setLayout(widgetList);
  widgetList->addWidget(sellButton);
}