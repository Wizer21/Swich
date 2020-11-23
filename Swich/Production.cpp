#include "Production.h"

Production::Production()
{
  idButton = 0;
  lockedPrice1 = 2000 + Utils::randZeroToVal(2000);
  lockedPrice2 = 5000 + Utils::randZeroToVal(5000);

  setProduction();
  loadDB();
}

void Production::setProduction()
{
  layoutProduction = new QGridLayout(this);

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

  layoutProduction->addWidget(newFactoryWidget("Paris"), 2, 0, 1, 3);
  hidedWidget.at(0)->setVisible(true);
  layoutProduction->addWidget(lockedFactory1, 3, 0, 1, 3);
  layoutProduction->addWidget(lockedFactory2, 4, 0, 1, 3);

  displayProduction->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  dailyProduction->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
  investedProduction->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  testInvested->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  connect(lockedFactory1, SIGNAL(clicked()), this, SLOT(askNewFactory()));
  connect(lockedFactory2, SIGNAL(clicked()), this, SLOT(askNewFactory()));

  // Theme
  lockedFactory1->setFixedHeight(this->height() * 0.18);
  lockedFactory2->setFixedHeight(this->height() * 0.18);

  lockedFactory1->setObjectName("a0");
  lockedFactory2->setObjectName("a1");

  SingleData* getPix = getPix->getInstance();
  getPix->addButtoonToAdaptOnTheme("lock", lockedFactory1);
  getPix->addButtoonToAdaptOnTheme("lock", lockedFactory2);
  getPix->addLabelToAdaptOnFont(4, displayProduction);
  getPix->addLabelToAdaptOnFont(1.5, investedProduction);

  lockedFactory1->setIconSize(QSize(50, 50));
  lockedFactory2->setIconSize(QSize(50, 50));

  Factory fact1;
  Factory fact2;
  Factory fact3;
  listFactory.push_back(fact1);
  listFactory.push_back(fact2);
  listFactory.push_back(fact3);
  layoutProduction->addWidget(newFactoryWidget("Tokyo"), 3, 0, 1, 3);
  layoutProduction->addWidget(newFactoryWidget("London"), 4, 0, 1, 3);
  updateWidgets();

  lockedFactory1->setCursor(Qt::PointingHandCursor);
  lockedFactory2->setCursor(Qt::PointingHandCursor);
  displayProduction->setObjectName("lastProduction");
}

QWidget* Production::newFactoryWidget(QString getName)
{
  QWidget* widgetFactory = new QWidget(this);
  QGridLayout* layoutWidget = new QGridLayout(this);

  QLabel* iconFactory = new QLabel(this);
  QLabel* name = new QLabel(getName, this);
  QLabel* displayLevel = new QLabel(this);
  QLabel* textLvl = new QLabel("Lvl", this);
  QLabel* displayProductionFactory = new QLabel(this);
  QLabel* textProduction = new QLabel(tr("Last production"), this);
  QPushButton* upgrade = new QPushButton(this);

  widgetFactory->setLayout(layoutWidget);

  layoutWidget->addWidget(iconFactory, 0, 0);
  layoutWidget->addWidget(name, 0, 1);
  layoutWidget->addWidget(displayLevel, 0, 2, Qt::AlignRight);
  layoutWidget->addWidget(textLvl, 0, 3, Qt::AlignLeft);
  layoutWidget->addWidget(displayProductionFactory, 0, 4, Qt::AlignRight);
  layoutWidget->addWidget(textProduction, 0, 5, Qt::AlignLeft);
  layoutWidget->addWidget(upgrade, 0, 6);

  layoutWidget->setAlignment(upgrade, Qt::AlignRight);

  levelList.push_back(displayLevel);
  productionlist.push_back(displayProductionFactory);
  upgradeList.push_back(upgrade);

  layoutWidget->setContentsMargins(10, 5, 10, 5);

  SingleData* getPix = SingleData::getInstance();
  getPix->addButtoonToAdaptOnTheme("cash", upgrade);
  upgrade->setIcon(QIcon(getPix->getPixMapOnActualTheme("cash")));

  iconFactory->setPixmap(getPix->getPixmap("factory"));

  widgetFactory->setObjectName("factoryWidget");

  widgetFactory->setVisible(false);
  hidedWidget.push_back(widgetFactory);
  listLvl_Upgrade.push_back({textLvl, upgrade});

  connect(upgrade, SIGNAL(clicked()), this, SLOT(upgradeFactory()));
  return widgetFactory;

  upgrade->setIconSize(QSize(50, 50));
  upgrade->setCursor(Qt::PointingHandCursor);
  upgrade->setToolTip(tr("Upgrade this factory"));
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
  displayProduction->setStyleSheet("color:#64ffda; font-size:80px;background-color:transparent;");

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
    SingleData::getInstance()->deleteButtonOnAdress(lockedFactory1);
    lockedFactory1->setVisible(false);
    hidedWidget.at(1)->setVisible(true);
    updateWidgets();
  }
  if (id == 1)
  {
    SingleData::getInstance()->deleteButtonOnAdress(lockedFactory2);
    lockedFactory2->setVisible(false);
    hidedWidget.at(2)->setVisible(true);
    updateWidgets();
  }
}

void Production::loadDB()
{
  std::vector<std::pair<int, int>> factoryLevel_upgrade = ItemDAO::getInstance()->getFactory();

  int sizeList = (int)factoryLevel_upgrade.size();
  for (int i = 0; i < sizeList; i++)
  {
    listFactory.at(i).setLevel(factoryLevel_upgrade.at(i).first);
    listFactory.at(i).setUpgrade(factoryLevel_upgrade.at(i).second);
    levelList.at(i)->setText(QString::number(factoryLevel_upgrade.at(i).first));
    upgradeList.at(i)->setText(QString::number(factoryLevel_upgrade.at(i).second));
  }
  if (factoryLevel_upgrade.at(1).first != 1)
  {
    lockedFactory1->setVisible(false);
  }
  if (factoryLevel_upgrade.at(2).first != 1)
  {
    lockedFactory2->setVisible(false);
  }
}

void Production::saveToDB()
{
  factoryLevel_upgrade.clear();
  int sizeList = (int)listFactory.size();
  for (int i = 0; i < sizeList; i++)
  {
    factoryLevel_upgrade.push_back({listFactory.at(i).getLevel(), listFactory.at(i).getNextUpgrade()});
  }
  ItemDAO::getInstance()->pushFactory(factoryLevel_upgrade);
}