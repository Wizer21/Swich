#include "Dragwidget.h"

Dragwidget::Dragwidget(QWidget* parent, QString addNom, int addVolume, int addId)
{
  nom = addNom;
  volume = addVolume;
  id = addId;
}

void Dragwidget::mouseMoveEvent(QMouseEvent* event)
{
  if (!(event->buttons() & Qt::LeftButton))
    return;

  QDrag* drag = new QDrag(this);
  QMimeData* mimeData = new QMimeData();

  mimeData->setText(QString("%1$%2$%3").arg(nom).arg(volume).arg(id));

  drag->setMimeData(mimeData);
  drag->exec(Qt::MoveAction);
}

void Dragwidget::setVolume(int setVol)
{
  volume = setVol;
}