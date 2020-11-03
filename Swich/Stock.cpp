#include "Stock.h"

Stock::Stock()
{
  setStock();
}

void Stock::setStock()
{
  QGridLayout* layoutStock = new QGridLayout(this);

  QPushButton* volVente = new QPushButton(tr("Stock"), this);

  this->setLayout(layoutStock);

  layoutStock->addWidget(volVente, 0, 0);
}