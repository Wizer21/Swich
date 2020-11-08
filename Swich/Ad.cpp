#include "Ad.h"

Ad::Ad()
  : QWidget()
{
  idEmploye = 0;
  day = 0;
  setAd();
}

void Ad::setAd()
{
  layoutAd = new QGridLayout(this);
  QChartView* graphAd = new QChartView(iniGraph());

  QLabel* managment = new QLabel(tr("Manager"), this);
  DropEmployee* manager = new DropEmployee(this);
  QVBoxLayout* layoutManager = new QVBoxLayout(this);
  QWidget* widgetManageTempo = new QWidget(this);

  QLabel* design = new QLabel(tr("Designer"), this);
  DropEmployee* designer = new DropEmployee(this);
  QVBoxLayout* layoutDesigner = new QVBoxLayout(this);
  QWidget* widgetDesignerTempo = new QWidget(this);

  QLabel* artisan = new QLabel(tr("Artisan"), this);
  DropEmployee* artisana = new DropEmployee(this);
  QVBoxLayout* layoutArtisan = new QVBoxLayout(this);
  QWidget* widgetArtisanaTempo = new QWidget(this);

  QLabel* newEmploye = new QLabel(tr("New"), this);
  displayNewEmploye = new QWidget(this);

  DropEmployee* trash = new DropEmployee(this);
  QVBoxLayout* trashlayout = new QVBoxLayout(this);
  QLabel* trashlabel = new QLabel(this);

  iniGraph();
  this->setLayout(layoutAd);
  layoutAd->addWidget(graphAd, 0, 0, 2, 3);

  layoutAd->addWidget(managment, 2, 0, 1, 1);
  layoutAd->addWidget(manager, 3, 0, 1, 1);
  manager->setLayout(layoutManager);
  layoutManager->addWidget(widgetManageTempo);

  layoutAd->addWidget(design, 2, 1, 1, 1);
  layoutAd->addWidget(designer, 3, 1, 1, 1);
  designer->setLayout(layoutDesigner);
  layoutDesigner->addWidget(widgetDesignerTempo);

  layoutAd->addWidget(artisan, 2, 2, 1, 1);
  layoutAd->addWidget(artisana, 3, 2, 1, 1);
  artisana->setLayout(layoutArtisan);
  layoutArtisan->addWidget(widgetArtisanaTempo);

  layoutAd->addWidget(newEmploye, 0, 3, 1, 1);
  layoutAd->addWidget(displayNewEmploye, 1, 3, 2, 1);

  layoutAd->addWidget(trash, 3, 3, 1, 1);
  trash->setLayout(trashlayout);
  trashlayout->addWidget(trashlabel);

  manager->setObjectName("0");
  designer->setObjectName("1");
  artisana->setObjectName("2");

  layoutManager->setObjectName("l0");
  layoutDesigner->setObjectName("l1");
  layoutArtisan->setObjectName("l2");

  widgetManageTempo->setObjectName("a0");
  widgetDesignerTempo->setObjectName("a1");
  widgetArtisanaTempo->setObjectName("a2");
  displayNewEmploye->setObjectName("new");
  trash->setObjectName("trash");
  callNewEmploye();

  QPixmap pix(":/Swich/trash-can-outline.png");
  pix = pix.scaled(100, 100);
  trashlabel->setPixmap(pix);

  connect(manager, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(designer, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(artisana, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(trash, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
}

QChart* Ad::iniGraph()
{
  QChart* sellVolumeAd = new QChart();

  sellSeriesAd = new QLineSeries();

  sellVolumeAd->addSeries(sellSeriesAd);

  axeVVolumesAd = new QValueAxis(this);
  axeHVolumesAd = new QValueAxis(this);

  sellVolumeAd->addAxis(axeVVolumesAd, Qt::AlignLeft);
  sellVolumeAd->addAxis(axeHVolumesAd, Qt::AlignBottom);

  sellSeriesAd->attachAxis(axeVVolumesAd);
  sellSeriesAd->attachAxis(axeHVolumesAd);

  return sellVolumeAd;
}

void Ad::callNewEmploye()
{
  QWidget* getNew = this->findChild<QWidget*>("new");
  delete getNew;
  getNew = nullptr;

  DragEmployee* newEmplo1 = new DragEmployee("0", "Bob", "Web");
  layoutAd->addWidget(newEmplo1, 1, 3, 2, 1);
  newEmplo1->setObjectName("new");
}

QString Ad::getSalary_Production(int addDays)
{
  int lvls = 0;
  int salary = 0;
  double efficiency = 1;
  day += addDays;

  for (int i = 0; i < employeList.size(); i++)
  {
    lvls += employeList.at(i)->getLvl();
  }
  for (int i = 0; i < lvls; i++)
  {
    efficiency += 0.1 + Static::randOnlyPositivePercentage(15);
  }
  for (int i = 0; i < employeList.size(); i++)
  {
    salary += employeList.at(i)->getSalary();
    lvls += employeList.at(i)->getLvl();
  }
  if (day < 30)
  {
    salary = 0;
  }
  else
  {
    day -= 30;
  }

  callNewEmploye();
  return QString("%1$%2").arg(salary).arg(efficiency);
}

void Ad::employeChanged(QString IdPhoto, int Level, QString Name, QString Talent, int Salary, int id, int pos)
{
  bool emptyDestination = true;
  if (sender()->objectName() == "trash")
  {
    if (pos == -1)
    {
      return;
    }
    for (int i = 0; i < employeList.size(); i++)
    {
      if (employeList.at(i)->getId() == id)
      {
        delete employeList.at(i);
        employeList.at(i) = nullptr;
        employeList.erase(employeList.begin() + i);
        return;
      }
    }
  }
  if (id == -1)
  {
    QWidget* getNewE = this->findChild<QWidget*>("new");
    delete getNewE;
    getNewE = nullptr;

    DragEmployee* newEmploye = new DragEmployee(IdPhoto, Level, Name, Talent, Salary, idEmploye++, sender()->objectName().toInt());
    QVBoxLayout* layoutToAdd = this->findChild<QVBoxLayout*>("l" + sender()->objectName());
    layoutToAdd->addWidget(newEmploye);
    employeList.push_back(newEmploye);
    newEmploye->setObjectName("z");
    return;
  }
  for (int i = 0; i < employeList.size(); i++)
  {
    if (employeList.at(i)->getPos() == sender()->objectName().toInt())
    {
      emptyDestination = false;
    }
  }
  if (emptyDestination)
  {
    int pos1 = -2;
    int pos1List = -2;
    for (int i = 0; i < employeList.size(); i++)
    {
      if (employeList.at(i)->getPos() == pos)
      {
        pos1 = employeList.at(i)->getPos();
        pos1List = i;
      }
    }
    QVBoxLayout* getLFrom = this->findChild<QVBoxLayout*>("l" + QString::number(pos1));
    getLFrom->removeWidget(employeList.at(pos1List));
    QVBoxLayout* getLTo = this->findChild<QVBoxLayout*>("l" + sender()->objectName());

    getLTo->addWidget(employeList.at(pos1List));

    employeList.at(pos1List)->setPos(sender()->objectName().toInt());
  }
  else
  {
    int pos1 = -2;
    int pos1List = -2;
    int pos2 = -2;
    int pos2List = -2;
    for (int i = 0; i < employeList.size(); i++)
    {
      if (employeList.at(i)->getPos() == pos)
      {
        pos1 = employeList.at(i)->getPos();
        pos1List = i;
      }
      else if (employeList.at(i)->getPos() == sender()->objectName().toInt())
      {
        pos2 = employeList.at(i)->getPos();
        pos2List = i;
      }
    }
    QVBoxLayout* getLFrom = this->findChild<QVBoxLayout*>("l" + QString::number(pos1));
    getLFrom->removeWidget(employeList.at(pos1List));
    QVBoxLayout* getLTo = this->findChild<QVBoxLayout*>("l" + QString::number(pos2));
    getLTo->removeWidget(employeList.at(pos2List));

    getLTo->addWidget(employeList.at(pos1List));
    getLFrom->addWidget(employeList.at(pos2List));

    employeList.at(pos1List)->setPos(sender()->objectName().toInt());
    employeList.at(pos2List)->setPos(pos);
  }
}