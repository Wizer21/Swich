#include "Ad.h"

Ad::Ad()
  : QWidget()
{
  setAd();
}

void Ad::setAd()
{

  QGridLayout* layoutAd = new QGridLayout(this);

  QWidget* widgetMenuLeft = new QWidget(this);
  QVBoxLayout* widgetList = new QVBoxLayout(this);
  QPushButton* volVente = new QPushButton(tr("Ad"), this);

  this->setLayout(layoutAd);

  layoutAd->addWidget(widgetMenuLeft, 0, 0);
  widgetMenuLeft->setLayout(widgetList);
  widgetList->addWidget(volVente);
}
