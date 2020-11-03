#include "Production.h"

Production::Production()
{
  setProduction();
}

void Production::setProduction()
{
  QGridLayout* layoutProduction = new QGridLayout(this);

  QPushButton* bouton = new QPushButton("Prod", this);

  this->setLayout(layoutProduction);

  layoutProduction->addWidget(bouton, 0, 0);
}