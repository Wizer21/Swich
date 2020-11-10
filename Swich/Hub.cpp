#include "Hub.h"

Hub::Hub()
{
  day = 0;
  month = 0;
  year = 0;
  date_1 = "00/00/00";
  gain_1 = "";
  bank_1 = "";
  setHub();
}

void Hub::setHub()
{
  QGridLayout* layoutHub = new QGridLayout(this);
  //top
  QWidget* widgetHubTop = new QWidget(this);
  QGridLayout* gridTop = new QGridLayout(this);
  QLabel* evo = new QLabel(tr("Evolution over the last Year"), this);
  bankEvo = new QLabel("test", this);
  prodEvo = new QLabel("test", this);
  sellsEvo = new QLabel("test", this);
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
  gridTop->addWidget(evo, 0, 0);
  gridTop->addWidget(bankEvo, 1, 0);
  gridTop->addWidget(prodEvo, 2, 0);
  gridTop->addWidget(sellsEvo, 3, 0);
  gridTop->addWidget(newMonth, 4, 0);

  layoutHub->addWidget(uptdateWidget, 0, 1);
  uptdateWidget->setLayout(gridRight);
  gridRight->addWidget(displayGain, 0, 0, 2, 2);
  gridRight->addWidget(displaySells, 1, 0, 1, 1);
  gridRight->addWidget(displayDate, 2, 0, 1, 1);

  gridRight->setSpacing(50);
  QFont font(qApp->font());
  font.setPixelSize(50);
  displayGain->setFont(font);

  //bot
  layoutHub->addWidget(widgetHubBot, 1, 0, 1, 2);
  widgetHubBot->setLayout(layoutGridBot);
  setDefaultWidgets();

  gridTop->setObjectName("grid");

  connect(newMonth, SIGNAL(clicked()), this, SLOT(newMonthClicked()));
}

void Hub::updateLabels(std::vector<double> bankHisto, std::vector<int> volHisto)
{
  double bankThisYear = 0;
  double bankLastYear = 0;
  double volThisYear = 0;
  double volLastYear = 0;

  for (int i = 0; i < 12; i++)
  {
    bankThisYear += bankHisto.at(i);
    volThisYear += volHisto.at(i);
  }

  for (int i = 12; i < 24; i++)
  {
    bankLastYear += bankHisto.at(i);
    volLastYear += volHisto.at(i);
  }
  bankEvo->setText("+" + QString::number(round(bankThisYear / bankLastYear * 100)) + "% Bank");
  //prodEvo->setText("+" + QString::number(evoProd) + "% Production");
  sellsEvo->setText("+" + QString::number(round(volThisYear / volLastYear * 100)) + "% Sells");
}

QString Hub::updateCurrentMonth(int gain, int sells, int addDays)
{
  QString cGain = QString::number(gain);

  if (gain >= 0)
  {
    cGain.insert(0, "+");
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
    gridLayoutWT->addWidget(bankCT, 2, 1, 1, 2);

    date.insert(date.begin(), dateCT);
    gain.insert(gain.begin(), gainCT);
    bank.insert(bank.begin(), bankCT);

    layoutGridBot->addWidget(widgetContainerT, 0, pos--);

    gainCT->setAlignment(Qt::AlignRight);
    bankCT->setAlignment(Qt::AlignRight);
    gridLayoutWT->setSpacing(0);
    gainCT->setFont(QFont("", 20));
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
      gain.at(i)->setStyleSheet("color:#ff3f3f;");
    }
    else
    {
      gain.at(i)->setStyleSheet("color:#51ff41;");
    }
  }
}