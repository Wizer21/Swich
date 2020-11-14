#include "DropEmployee.h"

DropEmployee::DropEmployee(QWidget* parent)
{
  this->setAcceptDrops(true);
}

void DropEmployee::dragEnterEvent(QDragEnterEvent* event)
{
  event->accept();
}

void DropEmployee::dragMoveEvent(QDragMoveEvent* event)
{
  event->accept();
}

void DropEmployee::dropEvent(QDropEvent* event)
{
  auto lText = event->mimeData()->text().split("$");
  emit transfertDataEmployee(lText.at(0).toInt(), lText.at(1).toInt());
}