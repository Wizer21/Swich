#include "DropEmployee.h"

DropEmployee::DropEmployee(QWidget* parent)
  : QWidget(parent)
{
  this->setAcceptDrops(true);
  type = "none";
  trashable = false;
}

void DropEmployee::dragEnterEvent(QDragEnterEvent* event)
{
  auto lText = event->mimeData()->text().split("$");

  if (lText.at(3).toInt() == 1 && trashable)
  {
    event->accept();
    return;
  }
  if (lText.at(2) == type && !trashable)
  {
    event->accept();
    return;
  }
}

void DropEmployee::dragMoveEvent(QDragMoveEvent* event)
{
  auto lText = event->mimeData()->text().split("$");

  if (lText.at(3) == 1 && trashable == true)
  {
    event->accept();
    return;
  }

  if (lText.at(2) == type)
  {
    event->accept();
    return;
  }
}

void DropEmployee::dropEvent(QDropEvent* event)
{
  auto lText = event->mimeData()->text().split("$");

  emit transfertDataEmployee(lText.at(0).toInt(), lText.at(1).toInt());
}

void DropEmployee::setAcceptableType(QString newType)
{
  type = newType;
}

void DropEmployee::setIsTrash(bool isTrash)
{
  trashable = isTrash;
}