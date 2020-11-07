#include "Ad.h"

Ad::Ad()
  : QWidget()
{
  setAd();
}

void Ad::setAd()
{

  QGridLayout* layoutAd = new QGridLayout(this);

  QWidget* widgetAdLeft = new QWidget(this);
  QGridLayout* layoutLeft = new QGridLayout(this);
  QLabel* management = new QLabel(tr("Managment"), this);
  QWidget* manager = new QWidget(this);
  QLabel* design = new QLabel(tr("Design"), this);
  QWidget* designer = new QWidget(this);
  QLabel* conception = new QLabel(tr("Conception"), this);
  QWidget* concept = new QWidget(this);
  QWidget* trash = new QWidget(this);

  QWidget* widgetAdRight = new QWidget(this);
  QGridLayout* grid = new QGridLayout(this);

  QPushButton* buton_1 = new QPushButton(this);
  QPushButton* buton_2 = new QPushButton(this);

  this->setLayout(layoutAd);

  layoutAd->addWidget(widgetAdLeft, 0, 0);
  widgetAdLeft->setLayout(layoutLeft);
  layoutLeft->addWidget(management, 0, 2, 1, 3);
  layoutLeft->addWidget(manager, 1, 2, 1, 3);
  layoutLeft->addWidget(design, 2, 1, 1, 3);
  layoutLeft->addWidget(designer, 3, 1, 1, 3);
  layoutLeft->addWidget(conception, 4, 0, 1, 3);
  layoutLeft->addWidget(concept, 5, 0, 1, 3);
  layoutLeft->addWidget(trash, 4, 4, 2, 1);

  layoutAd->addWidget(widgetAdRight, 0, 1);
  widgetAdRight->setLayout(grid);
  grid->addWidget(buton_1, 1, 0, 1, 1);
  grid->addWidget(buton_2, 2, 2, 1, 1);

  buton_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  buton_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //test
  manager->setStyleSheet("background-color:#111111;");
  designer->setStyleSheet("background-color:#111111;");
  concept->setStyleSheet("background-color:#111111;");
  trash->setStyleSheet("background-color:#111111;");
}
