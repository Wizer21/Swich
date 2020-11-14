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

  teamValueDisplay = new QLabel("+100%", this);
  QLabel* valueText = new QLabel(tr("Increase in sales estimates"), this);

  QGroupBox* groupTeam = new QGroupBox(tr("Team"), this);
  QHBoxLayout* layoutGroup = new QHBoxLayout(this);

  DropEmployee* manager = new DropEmployee(this);
  QVBoxLayout* layoutManager = new QVBoxLayout(this);

  DropEmployee* designer = new DropEmployee(this);
  QVBoxLayout* layoutDesigner = new QVBoxLayout(this);

  DropEmployee* artisana = new DropEmployee(this);
  QVBoxLayout* layoutArtisan = new QVBoxLayout(this);

  DropEmployee* commercial = new DropEmployee(this);
  layoutcommercial = new QVBoxLayout(this);

  QLabel* newEmploye = new QLabel(tr("New"), this);
  displayNewEmploye = new QWidget(this);

  QWidget* widgetTrash = new QWidget(this);
  QVBoxLayout* layoutTrash = new QVBoxLayout(this);
  DropEmployee* trash = new DropEmployee(this);
  QVBoxLayout* trashlayout = new QVBoxLayout(this);
  QLabel* trashlabel = new QLabel(this);

  this->setLayout(layoutAd);

  layoutAd->addWidget(teamValueDisplay, 2, 0, 1, 4);
  layoutAd->addWidget(valueText, 1, 0, 1, 4);

  layoutAd->addWidget(groupTeam, 3, 0, 2, 6);
  groupTeam->setLayout(layoutGroup);
  layoutGroup->addWidget(manager);
  layoutGroup->addWidget(designer);
  layoutGroup->addWidget(artisana);

  manager->setLayout(layoutManager);

  designer->setLayout(layoutDesigner);

  artisana->setLayout(layoutArtisan);

  layoutAd->addWidget(newEmploye, 0, 5, 1, 1);
  layoutAd->addWidget(displayNewEmploye, 0, 6, 3, 2);

  layoutAd->addWidget(widgetTrash, 2, 5, 1, 1);
  widgetTrash->setLayout(layoutTrash);
  layoutTrash->addWidget(trash);
  trash->setLayout(trashlayout);
  trashlayout->addWidget(trashlabel);

  layoutAd->addWidget(commercial, 3, 6, 1, 2);
  commercial->setLayout(layoutcommercial);

  manager->setObjectName("0");
  designer->setObjectName("1");
  artisana->setObjectName("2");

  layoutManager->setObjectName("l0");
  layoutDesigner->setObjectName("l1");
  layoutArtisan->setObjectName("l2");

  layoutGroup->setContentsMargins(0, 0, 0, 0);

  commercial->setAcceptableType("commercial");
  layoutTrash->setAlignment(Qt::AlignBottom);
  displayNewEmploye->setObjectName("new");
  trash->setObjectName("trash");
  callNewEmploye();
  trash->setMaximumSize(100, 100);
  trash->setMaximumSize(100, 100);
  groupTeam->setMinimumHeight(200);
  groupTeam->setMinimumWidth(500);
  trash->setIsTrash(true);

  layoutAd->setAlignment(valueText, Qt::AlignBottom | Qt::AlignRight);
  layoutAd->setAlignment(teamValueDisplay, Qt::AlignTop | Qt::AlignRight);
  layoutAd->setAlignment(newEmploye, Qt::AlignRight);

  manager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  designer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  artisana->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QPixmap pix(":/Swich/trash-can-outline.png");
  pix = pix.scaled(100, 100, Qt::KeepAspectRatio);
  trashlabel->setPixmap(pix);
  QFont font(qApp->font());
  teamValueDisplay->setFont(QFont(font.toString(), 45));

  connect(manager, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(designer, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(artisana, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(trash, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeeToTrash(const int&, const int&)));
  connect(commercial, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(commercialChanged(const int&, const int&)));

  //Theme
  teamValueDisplay->setObjectName("titleAd");
}

void Ad::callNewEmploye()
{
  DragEmployee* getNew = this->findChild<DragEmployee*>("new");
  delete getNew;
  getNew = nullptr;

  DragEmployee* newEmplo1 = new DragEmployee();
  layoutAd->addWidget(newEmplo1, 0, 6, 3, 2);
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

void Ad::employeChanged(const int& id, const int& pos)
{
  bool emptyDestination = true;
  int sizeList = (int)employeList.size();
  int idOldEmploye = 0;

  for (int i = 0; i < sizeList; i++)
  {
    if (employeList.at(i)->getPos() == sender()->objectName().toInt())
    {
      emptyDestination = false;
      idOldEmploye = i;
    }
  }
  if (id == -1)
  {
    if (!emptyDestination)
    {
      delete employeList.at(idOldEmploye);
      employeList.at(idOldEmploye) = nullptr;
      employeList.erase(employeList.begin() + idOldEmploye);
      setTotalLvl();
    }
    DragEmployee* getNewE = this->findChild<DragEmployee*>("new");
    layoutAd->removeWidget(getNewE);

    QVBoxLayout* layoutToAdd = this->findChild<QVBoxLayout*>("l" + sender()->objectName());
    layoutToAdd->addWidget(getNewE);
    employeList.push_back(getNewE);
    getNewE->setObjectName("z");
    getNewE->setId(idEmploye++);
    getNewE->setTrashable(true);
    getNewE->setPos(sender()->objectName().toInt());
    setTotalLvl();
    return;
  }
  if (emptyDestination)
  {
    int pos1 = -2;
    int pos1List = -2;
    for (int i = 0; i < sizeList; i++)
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
    for (int i = 0; i < sizeList; i++)
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

void Ad::employeeToTrash(const int& id, const int& pos)
{
  int sizeEmploye = employeList.size();

  if (commercial.size() > 0)
  {
    if (commercial.at(0)->getId() == id)
    {
      delete commercial.at(0);
      commercial.at(0) = nullptr;
      commercial.erase(commercial.begin());
      setTotalLvl();
      emit fireCommercial();
      return;
    }
  }
  for (int i = 0; i < sizeEmploye; i++)
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

void Ad::commercialChanged(const int& id, const int& pos)
{
  if (id == -1)
  {
    if (commercial.size() > 0)
    {
      delete commercial.at(0);
      commercial.at(0) = nullptr;
      commercial.erase(commercial.begin());
    }
    DragEmployee* getNewC = this->findChild<DragEmployee*>("new");
    layoutAd->removeWidget(getNewC);

    layoutcommercial->addWidget(getNewC);
    commercial.push_back(getNewC);
    getNewC->setId(idEmploye++);
    getNewC->setTrashable(true);
    getNewC->setObjectName("z");
    setTotalLvl();
    emit newCommercial(getNewC);
  }
}

void Ad::setTotalLvl()
{
  int totalLvl = 0;
  for (int i = 0; i < employeList.size(); i++)
  {
    totalLvl += employeList.at(i)->getLvl();
  }
}