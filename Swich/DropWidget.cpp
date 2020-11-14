#include "DropWidget.h"

DropWidget::DropWidget(QWidget* parent)
  : QScrollArea(parent)
{
  this->setAcceptDrops(true);
}

void DropWidget::dragEnterEvent(QDragEnterEvent* event)
{
  auto lText = event->mimeData()->text().split("$");
  if (lText.at(1).toInt() == 0)
  {
    event->ignore();
  }
  else
  {
    event->accept();
  }
}

void DropWidget::dragMoveEvent(QDragMoveEvent* event)
{
  auto lText = event->mimeData()->text().split("$");
  if (lText.at(1).toInt() == 0)
  {
    event->ignore();
  }
  else
  {
    event->accept();
  }
}

void DropWidget::dropEvent(QDropEvent* event)
{
  auto lText = event->mimeData()->text().split("$");
  emit transfertData(lText.at(0), lText.at(1), lText.at(2).toInt());
}