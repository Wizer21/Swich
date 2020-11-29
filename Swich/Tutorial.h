#pragma once
#include <QDialog>
#include "stdafx.h"
#include "SingleData.h"

class Tutorial : public QDialog
{
  Q_OBJECT

public:
  static Tutorial* getInstance()
  {
    if (!instance)
      instance = new Tutorial;
    return instance;
  }
  void tutorialOpened(int currentId, QPoint corner);
  void pageChanged(int idPage);
  void mooved(QPoint corner);

public slots:
  void boxCheched(int);

signals:
  void tutorialMooved(QPoint);

protected:
  void Tutorial::closeEvent(QCloseEvent* e);
  void Tutorial::moveEvent(QMoveEvent* event);

private:
  Tutorial();
  static Tutorial* instance;
  bool isOpen;
  bool isDocked;
  QGridLayout* layout;
  QLabel* isTitle;
  QTextEdit* containText;
  QStringList titles;
  QStringList listText;

  ~Tutorial();
};
