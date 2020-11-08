#include "DragEmployee.h"

DragEmployee::DragEmployee(DragEmployee* getEmploye)
{
  idPhoto = getEmploye->idPhoto;
  level = getEmploye->level;
  name = getEmploye->name;
  talent = getEmploye->talent;
  salary = getEmploye->salary;
  id = getEmploye->id;
  pos = getEmploye->pos;
  ini();
}

DragEmployee::DragEmployee(QString addIdPhoto, int addLevel, QString addName, QString addTalent, int addSalary, int addId, int addPos)
{
  idPhoto = addIdPhoto;
  level = addLevel;
  name = addName;
  talent = addTalent;
  salary = addSalary;
  id = addId;
  pos = addPos;
  ini();
}

void DragEmployee::ini()
{
  QGridLayout* layoutEmployee = new QGridLayout(this);
  QLabel* displayPix = new QLabel(this);
  QLabel* displayLvl = new QLabel(QString::number(level), this);
  QLabel* displayName = new QLabel(name, this);
  QLabel* displayTalent = new QLabel(talent, this);
  QLabel* displaySalary = new QLabel(QString::number(salary), this);

  this->setLayout(layoutEmployee);
  layoutEmployee->addWidget(displayPix, 0, 0);
  layoutEmployee->addWidget(displayLvl, 0, 1);
  layoutEmployee->addWidget(displayName, 1, 0);
  layoutEmployee->addWidget(displayTalent, 2, 0);
  layoutEmployee->addWidget(displaySalary, 3, 0);
}

void DragEmployee::mouseMoveEvent(QMouseEvent* event)
{
  if (!(event->buttons() & Qt::LeftButton))
    return;

  QDrag* drag = new QDrag(this);
  QMimeData* mimeData = new QMimeData();

  mimeData->setText(QString("%1$%2$%3$%4$%5$%6$%7").arg(idPhoto).arg(level).arg(name).arg(talent).arg(salary).arg(id).arg(pos));

  drag->setMimeData(mimeData);
  drag->exec(Qt::MoveAction);
}

int DragEmployee::getPos()
{
  return pos;
}

int DragEmployee::getId()
{
  return id;
}

void DragEmployee::setPos(int addPos)
{
  pos = addPos;
}