#include "Hub.h"

Hub::Hub()
{
  day = 0;
  month = 0;
  year = 0;
  date_1 = "00/00/00";
  gain_1 = "0";
  bank_1 = "0";
  setHub();
}

void Hub::setHub()
{
  QGridLayout* layoutHub = new QGridLayout(this);
  //top
  QWidget* widgetHubTop = new QWidget(this);
  QGridLayout* gridTop = new QGridLayout(this);
  QLabel* evo = new QLabel(tr("High Scores"), this);
  bankMax = new QLabel("0", this);
  QLabel* textBankMax = new QLabel(tr("Top Bank"), this);
  prodMax = new QLabel("0", this);
  QLabel* textProdMax = new QLabel(tr("Top Production"), this);
  sellsMax = new QLabel("0", this);
  QLabel* textSellMax = new QLabel(tr("Top Sales"), this);
  QPushButton* newMonth = new QPushButton(tr("Reach new month !"), this);

  QWidget* uptdateWidget = new QWidget(this);
  QGridLayout* gridRight = new QGridLayout(this);
  displayGain = new QLabel(this);
  displaySells = new QLabel(this);
  displayDate = new QLabel(this);

  // bot
  QWidget* widgetHubBot = new QWidget(this);
  layoutGridBot = new QGridLayout(this);

  //top
  this->setLayout(layoutHub);
  layoutHub->addWidget(widgetHubTop, 0, 0);
  widgetHubTop->setLayout(gridTop);
  gridTop->addWidget(evo, 0, 0, 1, 2);
  gridTop->addWidget(bankMax, 1, 0, Qt::AlignRight);
  gridTop->addWidget(textBankMax, 1, 1);
  gridTop->addWidget(prodMax, 2, 0, Qt::AlignRight);
  gridTop->addWidget(textProdMax, 2, 1);
  gridTop->addWidget(sellsMax, 3, 0, Qt::AlignRight);
  gridTop->addWidget(textSellMax, 3, 1);
  gridTop->addWidget(newMonth, 4, 0, 1, 2);

  layoutHub->addWidget(uptdateWidget, 0, 1);
  uptdateWidget->setLayout(gridRight);
  gridRight->addWidget(displayGain, 0, 0, Qt::AlignRight);
  gridRight->addWidget(displaySells, 1, 0, Qt::AlignRight);
  gridRight->addWidget(displayDate, 2, 0, Qt::AlignRight);

  gridRight->setSpacing(50);

  SingleData::getInstance()->addLabelToAdaptOnFont(3, displayGain);

  //bot
  layoutHub->addWidget(widgetHubBot, 1, 0, 1, 2);
  widgetHubBot->setLayout(layoutGridBot);
  setDefaultWidgets();

  connect(newMonth, SIGNAL(clicked()), this, SLOT(newMonthClicked()));

  //Theme
  newMonth->setCursor(Qt::PointingHandCursor);
  updateCurrentMonth(0, 0, 0);
  setColorScroll();
  widgetHubBot->setObjectName("hubScroll");
  evo->setObjectName("hubEvolution");
  uptdateWidget->setObjectName("lastIteration");

  newMonth->setToolTip(tr("Begin a new iteration"));
  uptdateWidget->setToolTip(tr("Result of the last month"));
  widgetHubBot->setToolTip(tr("Result of the last 6 month"));
}

void Hub::updateLabels(double addBank, double addProd, double addSell)
{
  if (addBank > storeMaxBank)
  {
    storeMaxBank = addBank;
    bankMax->setText(QString::number(round(addBank)));
    bankMax->setStyleSheet("color: #ffd740; font-size:22px;");
  }
  if (addProd > storeMaxProd)
  {
    storeMaxProd = addProd;
    prodMax->setText(QString::number(round(addProd)));
    prodMax->setStyleSheet("color: #ffd740; font-size:22px;");
  }
  if (addSell > storeMaxSell)
  {
    storeMaxSell = addSell;
    sellsMax->setText(QString::number(round(addSell)));
    sellsMax->setStyleSheet("color: #ffd740; font-size:22px;");
  }
}

QString Hub::updateCurrentMonth(int newGain, int sells, int addDays)
{
  QString cGain = QString::number(newGain);

  if (newGain >= 0)
  {
    cGain.insert(0, "+");
    displayGain->setStyleSheet("color:#b2ff59; font-size:100px;background-color:transparent;");
  }
  else
  {
    displayGain->setStyleSheet("color:#ff5252; font-size:100px;background-color:transparent;");
  }

  displayGain->setText(cGain);
  displaySells->setText(QString::number(sells) + tr(" Items Sold"));

  day += addDays;

  while (day > 30)
  {
    day -= 30;
    month++;
    while (month > 12)
    {
      month -= 12;
      year++;
    }
  }

  QString dayToStr = QString::number(day).rightJustified(2, '0');
  QString monthToStr = QString::number(month).rightJustified(2, '0');
  QString yearToStr = "";

  if (QString(year).size() > 2)
  {
    yearToStr = yearToStr.right(2);
  }
  else
  {
    yearToStr = QString::number(year).rightJustified(2, '0');
  }
  QString finalDate = QString("%1/%2/%3").arg(dayToStr).arg(monthToStr).arg(yearToStr);
  displayDate->setText(finalDate);
  return finalDate;
}

void Hub::newMonthClicked()
{
  emit transfertNewMounth();
}

void Hub::setDefaultWidgets()
{
  int pos = 6;
  for (int i = 0; i < 6; i++)
  {
    QWidget* widgetContainerT = new QWidget(this);
    QGridLayout* gridLayoutWT = new QGridLayout(this);
    QLabel* dateCT = new QLabel("00/00/00", this);
    QLabel* gainCT = new QLabel("0", this);
    QLabel* bankCT = new QLabel("0", this);

    layoutGridBot->addWidget(widgetContainerT);
    widgetContainerT->setLayout(gridLayoutWT);
    gridLayoutWT->addWidget(dateCT, 0, 0, 1, 3);
    gridLayoutWT->addWidget(gainCT, 1, 0, 1, 3);
    gridLayoutWT->addWidget(bankCT, 2, 0, 1, 3);

    date.insert(date.begin(), dateCT);
    gain.insert(gain.begin(), gainCT);
    bank.insert(bank.begin(), bankCT);

    layoutGridBot->addWidget(widgetContainerT, 0, pos--);

    gainCT->setAlignment(Qt::AlignRight);
    bankCT->setAlignment(Qt::AlignRight);
    gridLayoutWT->setSpacing(0);

    widgetContainerT->setObjectName("widgetScroll");

    SingleData::getInstance()->addLabelToAdaptOnFont(2, gainCT);
  }
}

void Hub::updateAndScrollWidgets(QString newDate, QString newGain, QString newBank)
{
  for (int i = 1; i < 6; i++)
  {
    int pos = i - 1;
    date.at(pos)->setText(date.at(i)->text());
    gain.at(pos)->setText(gain.at(i)->text());
    bank.at(pos)->setText(bank.at(i)->text());
  }
  date.at(5)->setText(date_1);
  gain.at(5)->setText(gain_1);
  bank.at(5)->setText(bank_1);

  date_1 = newDate;
  gain_1 = newGain;
  bank_1 = QString::number(round(newBank.toDouble()));
  setColorScroll();
}

void Hub::setColorScroll()
{
  for (int i = 0; i < gain.size(); i++)
  {
    if (gain.at(i)->text().toInt() < 0)
    {
      gain.at(i)->setStyleSheet("color:#ff5252;font:");
    }
    else
    {
      gain.at(i)->setStyleSheet("color:#b2ff59;font:");
    }
  }
}