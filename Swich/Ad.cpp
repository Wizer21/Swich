#include "Ad.h"
#include "Utils.h"

Ad::Ad()
  : QWidget()
{
  idEmploye = 0;
  day = 0;
  setAd();
  setNewTableLoaded();
}

void Ad::setAd()
{
  layoutAd = new QGridLayout(this);

  teamValueDisplay = new QLabel("+100%", this);
  QLabel* valueText = new QLabel(tr("Last performance"), this);

  QGroupBox* groupTeam = new QGroupBox(tr("Team"), this);
  QVBoxLayout* layoutGroupTemporaire = new QVBoxLayout(this);
  QWidget* widgetTeam = new QWidget(this);
  QHBoxLayout* layoutGroup = new QHBoxLayout(this);

  DropEmployee* manager = new DropEmployee(this);
  QVBoxLayout* layoutManager = new QVBoxLayout(this);

  DropEmployee* designer = new DropEmployee(this);
  QVBoxLayout* layoutDesigner = new QVBoxLayout(this);

  DropEmployee* artisana = new DropEmployee(this);
  QVBoxLayout* layoutArtisan = new QVBoxLayout(this);

  QGroupBox* groupCommercial = new QGroupBox(tr("Commercial"), this);
  QVBoxLayout* widgetCommercial = new QVBoxLayout(this);
  DropEmployee* commercial = new DropEmployee(this);
  layoutcommercial = new QVBoxLayout(this);

  QGroupBox* groupNew = new QGroupBox(tr("New"), this);
  QVBoxLayout* layoutNewT = new QVBoxLayout(this);
  QWidget* widgetNewT = new QWidget(this);
  widgetNew = new QVBoxLayout(this);
  displayNewEmploye = new QWidget(this);

  QWidget* widgetTrash = new QWidget(this);
  QVBoxLayout* layoutTrash = new QVBoxLayout(this);
  DropEmployee* trash = new DropEmployee(this);
  QVBoxLayout* trashlayout = new QVBoxLayout(this);
  QLabel* trashlabel = new QLabel(this);

  this->setLayout(layoutAd);

  layoutAd->addWidget(teamValueDisplay, 1, 0, 1, 4);
  layoutAd->addWidget(valueText, 0, 0, 1, 4);

  layoutAd->addWidget(groupTeam, 2, 0, 2, 6);
  groupTeam->setLayout(layoutGroupTemporaire);
  layoutGroupTemporaire->addWidget(widgetTeam);
  widgetTeam->setLayout(layoutGroup);
  layoutGroup->addWidget(manager);
  layoutGroup->addWidget(designer);
  layoutGroup->addWidget(artisana);

  manager->setLayout(layoutManager);

  designer->setLayout(layoutDesigner);

  artisana->setLayout(layoutArtisan);

  layoutAd->addWidget(groupNew, 0, 6, 2, 1);
  groupNew->setLayout(layoutNewT);
  layoutNewT->addWidget(widgetNewT);
  widgetNewT->setLayout(widgetNew);
  widgetNew->addWidget(displayNewEmploye);

  layoutAd->addWidget(widgetTrash, 1, 5, 1, 1);
  widgetTrash->setLayout(layoutTrash);
  layoutTrash->addWidget(trash);
  trash->setLayout(trashlayout);
  trashlayout->addWidget(trashlabel);

  layoutAd->addWidget(groupCommercial, 2, 6, 2, 1);
  groupCommercial->setLayout(widgetCommercial);
  widgetCommercial->addWidget(commercial);
  commercial->setLayout(layoutcommercial);

  manager->setObjectName("0");
  designer->setObjectName("1");
  artisana->setObjectName("2");

  layoutManager->setObjectName("l0");
  layoutDesigner->setObjectName("l1");
  layoutArtisan->setObjectName("l2");

  commercial->setAcceptCommercial(true);
  displayNewEmploye->setObjectName("new");
  trash->setObjectName("trash");
  callNewEmploye();
  trash->setIsTrash(true);

  SingleData* getData = getData->getInstance();

  getData->addLabelToAdaptOnTheme("trash", trashlabel);
  getData->addLabelToAdaptOnFont(4, teamValueDisplay);

  connect(manager, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(designer, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(artisana, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeChanged(const int&, const int&)));
  connect(trash, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(employeeToTrash(const int&, const int&)));
  connect(commercial, SIGNAL(transfertDataEmployee(const int&, const int&)), this, SLOT(commercialChanged(const int&, const int&)));

  //Theme
  groupTeam->setMinimumHeight(200);
  groupTeam->setMinimumWidth(500);
  layoutGroupTemporaire->setSpacing(0);
  layoutGroup->setContentsMargins(0, 0, 0, 0);
  groupNew->setMinimumHeight(195);
  groupNew->setMinimumWidth(groupNew->height() * 0.90);

  layoutTrash->setContentsMargins(0, 0, 0, 0);
  trashlayout->setContentsMargins(0, 0, 0, 0);

  layoutAd->setAlignment(groupNew, Qt::AlignBottom);
  layoutAd->setAlignment(valueText, Qt::AlignBottom | Qt::AlignRight);
  layoutAd->setAlignment(teamValueDisplay, Qt::AlignTop | Qt::AlignRight);
  trashlayout->setAlignment(trashlabel, Qt::AlignBottom | Qt::AlignRight);

  manager->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  designer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  artisana->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  teamValueDisplay->setObjectName("titleAd");
  groupTeam->setObjectName("groupTeam");
  groupCommercial->setObjectName("groupCommercial");
  groupNew->setObjectName("groupNew");
  teamValueDisplay->setToolTip(tr("Increase in sales volume due to your team"));
}

void Ad::callNewEmploye()
{
  DragEmployee* getNew = this->findChild<DragEmployee*>("new");
  delete getNew;
  getNew = nullptr;

  DragEmployee* newEmplo1 = new DragEmployee();
  widgetNew->addWidget(newEmplo1);
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
    efficiency += 0.1 + Utils::randOnlyPositivePercentage(15);
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

  teamValueDisplay->setText("+" + QString::number(efficiency * 100) + "%");
  teamValueDisplay->setStyleSheet("color:#b2ff59; font-size:80px;background-color:transparent;");
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
  }
}

void Ad::employeeToTrash(const int& id, const int& pos)
{
  int sizeEmploye = (int)employeList.size();

  if (commercialCurrent.size() > 0)
  {
    if (commercialCurrent.at(0)->getId() == id)
    {
      delete commercialCurrent.at(0);
      commercialCurrent.at(0) = nullptr;
      commercialCurrent.erase(commercialCurrent.begin());
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
      return;
    }
  }
}

void Ad::commercialChanged(const int& id, const int& pos)
{
  if (id == -1)
  {
    if (commercialCurrent.size() > 0)
    {
      delete commercialCurrent.at(0);
      commercialCurrent.at(0) = nullptr;
      commercialCurrent.erase(commercialCurrent.begin());
    }
    DragEmployee* getNewC = this->findChild<DragEmployee*>("new");
    layoutAd->removeWidget(getNewC);

    layoutcommercial->addWidget(getNewC);
    commercialCurrent.push_back(getNewC);
    getNewC->setId(idEmploye++);
    getNewC->setTrashable(true);
    getNewC->setObjectName("z");
    emit newCommercial(getNewC);
  }
}

void Ad::teamPushToDB()
{
  ItemDAO::getInstance()->pushEmployee(employeList, commercialCurrent);
}

void Ad::setNewTableLoaded()
{
  qDeleteAll(employeList.begin(), employeList.end());
  qDeleteAll(commercialCurrent.begin(), commercialCurrent.end());
  employeList.clear();
  commercialCurrent.clear();
  
  std::vector<DragEmployee*> temporaryList = ItemDAO::getInstance()->getEmployeList();
  int pos = 0;
  int sizeList = (int)temporaryList.size();

  for (int i = 0; i < sizeList; i++)
  {
    if (temporaryList.at(i)->getIsCommercial())
    {
      layoutcommercial->addWidget(temporaryList.at(i));
      temporaryList.at(i)->setId(idEmploye++);
      temporaryList.at(i)->setTrashable(true);
      temporaryList.at(i)->setObjectName("z");

      commercialCurrent.push_back(temporaryList.at(i));
    }
    else
    {
      QVBoxLayout* layoutToAdd = this->findChild<QVBoxLayout*>("l" + QString::number(pos++));
      layoutToAdd->addWidget(temporaryList.at(i));
      temporaryList.at(i)->setObjectName("z");
      temporaryList.at(i)->setId(idEmploye++);
      temporaryList.at(i)->setTrashable(true);
      temporaryList.at(i)->setPos(pos);

      employeList.push_back(temporaryList.at(i));
    }
  }
}