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

  //QWidget* widgetText = new QWidget(this);
  //QVBoxLayout* layoutText = new QVBoxLayout(this);
  displayProduction = new QLabel("0", this);
  QLabel* dailyProduction = new QLabel(tr("Last iteration production"), this);
  QLabel* investedProduction = new QLabel("1250", this);
  QLabel* testInvested = new QLabel(tr("Invested"), this);

  lockedFactory1 = new QPushButton(QString::number(lockedPrice1), this);
  lockedFactory2 = new QPushButton(QString::number(lockedPrice2), this);

  this->setLayout(layoutProduction);

  layoutProduction->addWidget(displayProduction, 0, 0);
  layoutProduction->addWidget(dailyProduction, 0, 1);
  layoutProduction->addWidget(investedProduction, 1, 0);
  layoutProduction->addWidget(testInvested, 1, 1);

  layoutProduction->addWidget(newFactoryWidget("Paris", "0"), 2, 0, 1, 3);
  layoutProduction->addWidget(lockedFactory1, 3, 0, 1, 3);
  layoutProduction->addWidget(lockedFactory2, 4, 0, 1, 3);

  displayProduction->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  dailyProduction->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
  investedProduction->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  testInvested->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  QFont font(qApp->font());
  font.setPixelSize(100);
  displayProduction->setFont(font);
  font.setPixelSize(50);
  investedProduction->setFont(font);

  connect(lockedFactory1, SIGNAL(clicked()), this, SLOT(askNewFactory()));
  connect(lockedFactory2, SIGNAL(clicked()), this, SLOT(askNewFactory()));

  // Theme
  lockedFactory1->setFixedHeight(this->height() * 0.15);
  lockedFactory2->setFixedHeight(this->height() * 0.15);

  lockedFactory1->setObjectName("a0");
  lockedFactory2->setObjectName("a1");
  QPixmap pix(":/Swich/lock-open-alert.png");
  pix = pix.scaled(100, 100);
  lockedFactory1->setIcon(QIcon(pix));
  lockedFactory2->setIcon(QIcon(pix));
  Factory fact1;
  listFactory.push_back(fact1);
  updateWidgets();

  displayProduction->setObjectName("lastProduction");
}

QWidget* Production::newFactoryWidget(QString getName, QString objName)
{
  QWidget* widgetFactory = new QWidget(this);
  QGridLayout* layoutWidget = new QGridLayout(this);

  QLabel* iconFactory = new QLabel(this);
  QLabel* name = new QLabel(getName, this);
  QLabel* textLvl = new QLabel("Lvl", this);
  QLabel* displayLevel = new QLabel(this);
  QLabel* textProduction = new QLabel(tr("Last production"), this);
  QLabel* displayProductionFactory = new QLabel(this);
  QPushButton* upgrade = new QPushButton(this);

  widgetFactory->setLayout(layoutWidget);

  layoutWidget->addWidget(iconFactory, 0, 0);
  layoutWidget->addWidget(name, 0, 1);
  layoutWidget->addWidget(textLvl, 0, 2);
  layoutWidget->addWidget(displayLevel, 0, 3);
  layoutWidget->addWidget(textProduction, 0, 4);
  layoutWidget->addWidget(displayProductionFactory, 0, 5);
  layoutWidget->addWidget(upgrade, 0, 6);

  layoutWidget->setAlignment(upgrade, Qt::AlignRight);

  textLvl->setAlignment(Qt::AlignBottom);
  textProduction->setAlignment(Qt::AlignBottom);

  levelList.push_back(displayLevel);
  productionlist.push_back(displayProductionFactory);
  upgradeList.push_back(upgrade);

  layoutWidget->setContentsMargins(10, 5, 10, 5);
  QPixmap pix(":/Swich/factoryDark.png");
  pix = pix.scaled(80, 80);
  iconFactory->setPixmap(pix);
  QPixmap pix1(":/Swich/cash-multiple.png");
  upgrade->setIcon(QIcon(pix1));
  upgrade->setIconSize(QSize(50, 50));
  widgetFactory->setStyleSheet("background-color:#565656;");

  upgrade->setObjectName(QString::number(idButton++));
  widgetFactory->setObjectName("factory" + objName);
  displayLevel->setObjectName("factoryLvl");

  connect(upgrade, SIGNAL(clicked()), this, SLOT(upgradeFactory()));
  return widgetFactory;
}

void Production::updateWidgets()
{
  for (int i = 0; i < listFactory.size(); i++)
  {
    levelList.at(i)->setText(QString::number(listFactory.at(i).getLevel()));
    productionlist.at(i)->setText(QString::number(round(listFactory.at(i).getProduction())));
    upgradeList.at(i)->setText(QString::number(listFactory.at(i).getNextUpgrade()));
    levelList.at(i)->setStyleSheet("font-size: 40px; color:#64ffda;");
    productionlist.at(i)->setStyleSheet("font-size: 40px; color:#64ffda;");
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
  levelList.at(id)->setText(QString::number(listFactory.at(id).getLevel()));
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
    layoutProduction->addWidget(newFactoryWidget("Tokyo", "1"), 3, 0, 1, 3);
    Factory fact2;
    listFactory.push_back(fact2);
    updateWidgets();
  }
  if (id == 1)
  {
    delete lockedFactory2;
    lockedFactory2 = nullptr;
    layoutProduction->addWidget(newFactoryWidget("London", "2"), 4, 0, 1, 3);
    Factory fact3;
    listFactory.push_back(fact3);
    updateWidgets();
  }
}