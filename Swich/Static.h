#pragma once
#include <random>
#include "stdafx.h"
#include <QString>
#include <QPixmap>
#include <QPair>
#include <QVector>

class Static : public QObject
{
  Q_OBJECT

public:
  static void iniCharacter();
  static void pushCharacter(const QString& addNom, const QString& pixMap);
  static QPair<QString, QPixmap*> getRandCharacter();
  static double randZeroToVal(const int& val);
  static double randNegativeIntToPercentage(const int& val);
  static double randOnlyPositivePercentage(const int& val);
  static const QVector<QPair<QString, QPixmap*>>* listCharacter = Static::iniCharacter();

private:
  explicit inline Static(){};
  inline ~Static(){};
};
