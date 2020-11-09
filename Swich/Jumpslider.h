#pragma once
#include <qslider.h>
#include <QMouseEvent>

class Jumpslider : public QSlider
{
public:
  Jumpslider(Qt::Orientation orientation, QWidget* parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent* event) override;
};
