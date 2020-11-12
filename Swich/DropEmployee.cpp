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
  emit transfertDataEmployee(lText.at(0), lText.at(1).toInt(), lText.at(2), lText.at(3), lText.at(4).toInt(), lText.at(5).toInt(), lText.at(6).toInt(), lText.at(7));
}