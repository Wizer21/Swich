#include "Jumpslider.h"

Jumpslider::Jumpslider(Qt::Orientation addOrientation, QWidget* parent)
  : QSlider(parent)
{
  setOrientation(addOrientation);
}

void Jumpslider::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    setValue(minimum() + ((maximum() - minimum()) * event->x()) / width());
    event->accept();
  }
}
