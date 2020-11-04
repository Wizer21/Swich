#pragma once
#include "stdafx.h"

class Dragwidget : public QWidget
{
public:
  Dragwidget(QWidget* parent, QString addNom, int addVolume, int addId);
  void setVolume(int setVol);

protected:
  void mouseMoveEvent(QMouseEvent* event);

private:
  QString nom;
  int volume;
  int id;
};
