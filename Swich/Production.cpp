#include "Production.h"

Production::Production()
{
  setProduction();
}

void Production::setProduction()
{
  QGridLayout* layoutProduction = new QGridLayout(this);

  QWidget* widgetText = new QWidget(this);
  QHBoxLayout* layoutText = new QHBoxLayout(this);
  QLabel* dailyProduction = new QLabel("Contain Daily prod", this);

  this->setLayout(layoutProduction);

  layoutProduction->addWidget(widgetText, 0, 0);
  widgetText->setLayout(layoutText);
  layoutText->addWidget(dailyProduction);

  layoutProduction->addWidget(newFactoryWidget(), 1, 0);
  layoutProduction->addWidget(newFactoryWidget(), 0, 1);
  layoutProduction->addWidget(newFactoryWidget(), 1, 1);

  listFactory.push_back(factoryFunctions.setUpNewOne());
  updateWidgets();
}

QWidget* Production::newFactoryWidget()
{
  QWidget* widgetFactory = new QWidget(this);
  QGridLayout* layoutWidget = new QGridLayout(this);
  QLabel* displayLevel = new QLabel(this);
  QLabel* displayProduction = new QLabel(this);
  QPushButton* upgrade = new QPushButton(this);

  widgetFactory->setLayout(layoutWidget);
  layoutWidget->addWidget(displayLevel, 0, 0);
  layoutWidget->addWidget(displayProduction, 1, 0);
  layoutWidget->addWidget(upgrade, 1, 1);

  levelList.push_back(displayLevel);
  productionlist.push_back(displayProduction);
  upgradeList.push_back(upgrade);

  return widgetFactory;
}

void Production::updateWidgets()
{
  for (int i = 0; i < listFactory.size(); i++)
  {
    levelList.at(i)->setText(QString::number(listFactory.at(i).getLevel()));
    productionlist.at(i)->setText(QString::number(listFactory.at(i).getProduction()));
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

  return QString("%1$%2").arg(totalProduction).arg(totalCost);
}
