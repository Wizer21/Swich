#include "Hub.h"

Hub::Hub()
{
  setHub();
}

void Hub::setHub()
{
  QGridLayout* layoutHub = new QGridLayout(this);

  QWidget* widgetMenuLeft = new QWidget(this);
  QVBoxLayout* widgetList = new QVBoxLayout(this);
  QPushButton* volVente = new QPushButton(tr("HUB"), this);

  this->setLayout(layoutHub);

  layoutHub->addWidget(widgetMenuLeft, 0, 0);
  widgetMenuLeft->setLayout(widgetList);
  widgetList->addWidget(volVente);
}