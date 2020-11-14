#include "DragEmployee.h"

DragEmployee::DragEmployee()
{
  QPair pair = Static::getRandCharacter();
  level = -1;
  name = pair.first;
  note = -1;
  salary = -1;
  id = -1;
  pos = -1;

  calculRandStats();
  ini(pair.second);
}

void DragEmployee::ini(const QPixmap* pix)
{
  QGridLayout* layoutEmployee = new QGridLayout(this);
  QLabel* displayPix = new QLabel(this);
  QLabel* displayLvl = new QLabel(note, this);
  QLabel* displayName = new QLabel(name, this);
  QLabel* displaySalary = new QLabel(QString::number(salary), this);

  displayPix->setPixmap(*pix);

  this->setLayout(layoutEmployee);
  layoutEmployee->addWidget(displayPix, 0, 0);
  layoutEmployee->addWidget(displayLvl, 0, 1);
  layoutEmployee->addWidget(displayName, 1, 0);
  layoutEmployee->addWidget(displaySalary, 2, 0);

  layoutEmployee->setAlignment(Qt::AlignTop);
}

void DragEmployee::calculRandStats()
{
  //Level
  bool diceValidated = true;
  int dice = 0;
  level = 0;
  while (diceValidated)
  {
    level += 1;
    dice = Static::randZeroToVal(100);
    if (dice < 25)
    {
      diceValidated = false;
    }
  }
  //Salary
  double calculSalary = 350 + Static::randZeroToVal(300);
  for (int i = 0; i < level; i++)
  {
    calculSalary *= (1.10 + Static::randOnlyPositivePercentage(10));
  }
  salary = calculSalary;
  note = calculNote(level);

  if (level < 3)
  {
    this->setStyleSheet("background-color:#ff5252");
  }
  else if (level < 6)
  {
    this->setStyleSheet("background-color:#7c4dff");
  }
  else if (level < 9)
  {
    this->setStyleSheet("background-color:#536dfe");
  }
  else if (level < 12)
  {
    this->setStyleSheet("background-color:#b2ff59");
  }
  else
  {
    this->setStyleSheet("QWidget{background-color:#ffd740;} QLabel{color:#262626;}");
  }
}

QString DragEmployee::calculNote(int lvl)
{
  int copylvl = lvl;
  QString newNote;
  switch (copylvl)
  {
    case 0:
      newNote = "D-";
      break;
    case 1:
      newNote = "D";
      break;
    case 2:
      newNote = "D+";
      break;
    case 3:
      newNote = "C-";
      break;
    case 4:
      newNote = "C";
      break;
    case 5:
      newNote = "C+";
      break;
    case 6:
      newNote = "B-";
      break;
    case 7:
      newNote = "B";
      break;
    case 8:
      newNote = "B+";
      break;
    case 9:
      newNote = "A-";
      break;
    case 10:
      newNote = "A";
      break;
    case 11:
      newNote = "A+";
      break;
    default:
      copylvl -= 12;
      newNote = "S";
      for (int i = 0; i < lvl; i++)
      {
        if (copylvl > 0)
        {
          newNote.insert(0, "S");
          copylvl--;
          if (copylvl > 0)
          {
            newNote += "+";
            copylvl--;
          }
        }
      }
  }
  return newNote;
}

void DragEmployee::mouseMoveEvent(QMouseEvent* event)
{
  if (!(event->buttons() & Qt::LeftButton))
    return;

  QDrag* drag = new QDrag(this);
  QMimeData* mimeData = new QMimeData();

  mimeData->setText(QString("%1$%2").arg(id).arg(pos));

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

int DragEmployee::getSalary()
{
  return salary;
}

int DragEmployee::getLvl()
{
  return level;
}