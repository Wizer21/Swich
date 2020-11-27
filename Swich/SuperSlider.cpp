#include "SuperSlider.h"

SuperSlider::SuperSlider(Qt::Orientation orientation, QWidget* parent)
  : QSlider(orientation, parent)
{
}

void SuperSlider::sliderChange(QAbstractSlider::SliderChange change)
{
  QSlider::sliderChange(change);

  if (change == QAbstractSlider::SliderValueChange)
  {
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    QPoint bottomRightCorner = sr.topLeft();

    QToolTip::showText(mapToGlobal(QPoint(bottomRightCorner.x() + 30, bottomRightCorner.y() - 21)), QString::number(value()), this);
  }
}

void SuperSlider::mousePressEvent(QMouseEvent* event)
{
  QStyleOptionSlider opt;
  initStyleOption(&opt);
  QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

  if (event->button() == Qt::LeftButton && sr.contains(event->pos()) == false)
  {
    int newVal;
    if (orientation() == Qt::Vertical)
      newVal = minimum() + ((maximum() - minimum()) * (height() - event->y())) / height();
    else
      newVal = minimum() + ((maximum() - minimum()) * event->x()) / width();

    if (invertedAppearance() == true)
      setValue(maximum() - newVal);
    else
      setValue(newVal);

    event->accept();
  }
  QSlider::mousePressEvent(event);
}