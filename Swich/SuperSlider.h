#pragma once
#include "stdafx.h"

class SuperSlider : public QSlider
{
public:
  SuperSlider(Qt::Orientation, QWidget* parent);

protected:
  virtual void sliderChange(SliderChange change);
  void mousePressEvent(QMouseEvent* event);
};
