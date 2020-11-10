#include "Production.h"

Production::Production()
{
  idButton = 0;
  lockedPrice1 = 2000 + Static::randZeroToVal(2000);
  lockedPrice2 = 5000 + Static::randZeroToVal(5000);

  setProduction();
}

void Production::setProduction()
{
  layoutProduction = new QGridLayout(this);

  QWidget* widgetText = new QWidget(this);
  QVBoxLayout* layoutText = new QVBoxLayout(this);
  QLabel* dailyProduction = new QLabel(tr("Last iteration production"), this);
  displayProduction = new QLabel("0", this);
  lockedFactory1 = new QPushButton(tr("Locked \n") + QString::number(lockedPrice1), this);
  lockedFactory2 = new QPushButton(tr("Locked \n") + QString::number(lockedPrice2), this);

  this->setLayout(layoutProduction);

  layoutProduction->addWidget(widgetText, 0, 0);
  widgetText->setLayout(layoutText);
  layoutText->addWidget(dailyProduction);
  layoutText->addWidget(displayProduction);

  layoutProduction->addWidget(newFactoryWidget(), 1, 0);
  layoutProduction->addWidget(lockedFactory1, 0, 1);
  layoutProduction->addWidget(lockedFactory2, 1, 1);

  layoutText->setSpacing(0);
  layoutText->setAlignment(Qt::AlignBottom);
  dailyProduction->setAlignment(Qt::AlignRight);
  displayProduction->setAlignment(Qt::AlignRight);
  QFont font(qApp->font());
  font.setPixelSize(50);
  displayProduction->setFont(font);
  lockedFactory1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  lockedFactory2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  lockedFactory1->setObjectName("a0");
  lockedFactory2->setObjectName("a1");
  Factory fact1;
  listFactory.push_back(fact1);
  updateWidgets();

  connect(lockedFactory1, SIGNAL(clicked()), this, SLOT(askNewFactory()));
  connect(lockedFactory2, SIGNAL(clicked()), this, SLOT(askNewFactory()));
}

QWidget* Production::newFactoryWidget()
{
  QWidget* widgetFactory = new QWidget(this);
  QGridLayout* layoutWidget = new QGridLayout(this);
  QLabel* iconFactory = new QLabel(this);
  QLabel* displayLevel = new QLabel(this);
  QLabel* displayProductionFactory = new QLabel(this);
  QPushButton* upgrade = new QPushButton(this);

  widgetFactory->setLayout(layoutWidget);
  layoutWidget->addWidget(iconFactory, 0, 0);
  layoutWidget->addWidget(displayLevel, 0, 1);
  layoutWidget->addWidget(displayProductionFactory, 1, 0);
  layoutWidget->addWidget(upgrade, 1, 1);

  levelList.push_back(displayLevel);
  productionlist.push_back(displayProductionFactory);
  upgradeList.push_back(upgrade);

  QPixmap pix(":/Swich/factoryDark.png");
  pix = pix.scaled(40, 40);
  iconFactory->setPixmap(pix);
  upgrade->setIcon(QIcon(":/Swich/cash-multiple.png"));
  upgrade->setObjectName(QString::number(idButton++));
  connect(upgrade, SIGNAL(clicked()), this, SLOT(upgradeFactory()));
  return widgetFactory;
}

void Production::updateWidgets()
{
  for (int i = 0; i < listFactory.size(); i++)
  {
    levelList.at(i)->setText("Lvl " + QString::number(listFactory.at(i).getLevel()));
    productionlist.at(i)->setText(QString::number(round(listFactory.at(i).getProduction())));
    upgradeList.at(i)->setText(QString::number(listFactory.at(i).getNextUpgrade()));
  }
}

QString Production::newMonthProd(int days)
{
  double totalProduction = 0;
  double totalCost = 0;
  for (int i = 0; i < listFactory.size(); i++)
  {
    listFactory.at(i).newMonthFactory(days);
    totalProduction += listFactory.at(i).getProduction();
    totalCost += listFactory.at(i).getCost();
  }
  updateWidgets();
  displayProduction->setText(QString::number(round(totalProduction)));

  return QString("%1$%2").arg(totalProduction).arg(totalCost);
}

void Production::upgradeFactory()
{
  int id = sender()->objectName().toInt();
  int cost = listFactory.at(id).getNextUpgrade();
  emit transfertUpgrade(cost, id);
}

void Production::validatedUpgrade(int id)
{
  listFactory.at(id).upgradeAccepted();
  upgradeList.at(id)->setText(QString::number(listFactory.at(id).getNextUpgrade()));
  levelList.at(id)->setText("Lvl " + QString::number(listFactory.at(id).getLevel()));
}

void Production::askNewFactory()
{
  QString getId = sender()->objectName().at(1);
  int id = getId.toInt();
  if (id == 0)
  {
    emit transfertNewFactory(lockedPrice1, id);
  }
  else
  {
    emit transfertNewFactory(lockedPrice2, id);
  }
}

void Production::validateNewFactory(int id)
{
  if (id == 0)
  {
    delete lockedFactory1;
    lockedFactory1 = nullptr;
    layoutProduction->addWidget(newFactoryWidget(), 0, 1);
    Factory fact2;
    listFactory.push_back(fact2);
    updateWidgets();
  }
  if (id == 1)
  {
    delete lockedFactory2;
    lockedFactory2 = nullptr;
    layoutProduction->addWidget(newFactoryWidget(), 1, 1);
    Factory fact3;
    listFactory.push_back(fact3);
    updateWidgets();
  }
}