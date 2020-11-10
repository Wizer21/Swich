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

  QLabel* team = new QLabel(tr("Your team"), this);

  displayTotalLvl = new QLabel("dab", this);

  DropEmployee* manager = new DropEmployee(this);
  QVBoxLayout* layoutManager = new QVBoxLayout(this);

  DropEmployee* designer = new DropEmployee(this);
  QVBoxLayout* layoutDesigner = new QVBoxLayout(this);

  DropEmployee* artisana = new DropEmployee(this);
  QVBoxLayout* layoutArtisan = new QVBoxLayout(this);

  QLabel* newEmploye = new QLabel(tr("New"), this);
  displayNewEmploye = new QWidget(this);

  QWidget* widgetTrash = new QWidget(this);
  QVBoxLayout* layoutTrash = new QVBoxLayout(this);
  DropEmployee* trash = new DropEmployee(this);
  QVBoxLayout* trashlayout = new QVBoxLayout(this);
  QLabel* trashlabel = new QLabel(this);

  this->setLayout(layoutAd);

  layoutAd->addWidget(team, 0, 0, 1, 1);
  layoutAd->addWidget(displayTotalLvl, 1, 1, 1, 1);

  layoutAd->addWidget(manager, 3, 0, 1, 1);
  manager->setLayout(layoutManager);

  layoutAd->addWidget(designer, 3, 1, 1, 1);
  designer->setLayout(layoutDesigner);

  layoutAd->addWidget(artisana, 3, 2, 1, 1);
  artisana->setLayout(layoutArtisan);

  layoutAd->addWidget(newEmploye, 0, 3, 1, 1);
  layoutAd->addWidget(displayNewEmploye, 1, 3, 2, 1);

  layoutAd->addWidget(widgetTrash, 3, 3, 1, 1);
  widgetTrash->setLayout(layoutTrash);
  layoutTrash->addWidget(trash);
  trash->setLayout(trashlayout);
  trashlayout->addWidget(trashlabel);

  manager->setObjectName("0");
  designer->setObjectName("1");
  artisana->setObjectName("2");

  layoutManager->setObjectName("l0");
  layoutDesigner->setObjectName("l1");
  layoutArtisan->setObjectName("l2");

  layoutTrash->setAlignment(Qt::AlignBottom);
  displayNewEmploye->setObjectName("new");
  trash->setObjectName("trash");
  callNewEmploye();
  trash->setMaximumSize(100, 100);
  trash->setMaximumSize(100, 100);

  manager->setStyleSheet("background-color:#C8C8C8;");
  designer->setStyleSheet("background-color:#C8C8C8;");
  artisana->setStyleSheet("background-color:#C8C8C8;");
  manager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  designer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  artisana->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QPixmap pix(":/Swich/trash-can-outline.png");
  pix = pix.scaled(100, 100);
  trashlabel->setPixmap(pix);

  connect(manager, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(designer, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(artisana, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
  connect(trash, SIGNAL(transfertDataEmployee(QString, int, QString, QString, int, int, int)), this, SLOT(employeChanged(QString, int, QString, QString, int, int, int)));
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
        setTotalLvl();
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
    setTotalLvl();
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
    setTotalLvl();
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
      if (employeList.at(i)->getPos() == sender()->objectName().toInt())
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
    setTotalLvl();
  }
}

void Ad::setTotalLvl()
{
  int totalLvl = 0;
  DragEmployee getEmploye;
  for (int i = 0; i < employeList.size(); i++)
  {
    totalLvl += employeList.at(i)->getLvl();
  }
  displayTotalLvl->setText(getEmploye.calculNote(totalLvl));
}