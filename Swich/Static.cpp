#include "Static.h"

void Static::iniCharacter()
{
  QVector<QPair<QString, QPixmap*>>* listCharacter = new QVector();

  Static::pushCharacter("Frederic", ":/Swich/Frederic.jpg");
  Static::pushCharacter("Francis", ":/Swich/Francis.jpg");
  Static::pushCharacter("Karine", ":/Swich/Karine.jpg");
  Static::pushCharacter("Marie", ":/Swich/Marie.jpg");
  Static::pushCharacter("Camille", ":/Swich/Camille.jpg");
  Static::pushCharacter("Emilie", ":/Swich/Emilie.jpg");
  Static::pushCharacter("Leonie", ":/Swich/Leonie.jpg");
  Static::pushCharacter("Bob", ":/Swich/Bob.jpg");
  Static::pushCharacter("Christophe", ":/Swich/Christophe.jpg");
  Static::pushCharacter("Maxime", ":/Swich/Maxime.jpg");
}

QPair<QString, QPixmap*> Static::getRandCharacter()
{
  return Static::listCharacter->at(randZeroToVal((int)Static::listCharacter->size()));
}

void Static::pushCharacter(const QString& addNom, const QString& pixMap)
{
  QPixmap* pix1 = new QPixmap(pixMap);
  QPixmap pix2 = pix1->scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
  delete pix1;
  pix1 = nullptr;
  QPixmap* newPix = new QPixmap(pix2);
  listCharacter->append(qMakePair(addNom, newPix));
}

double Static::randZeroToVal(const int& val)
{
  return rand() % val;
}

double Static::randNegativeIntToPercentage(const int& val)
{
  return (randZeroToVal(val) - randZeroToVal(val) * 2) * 0.01;
}

double Static::randOnlyPositivePercentage(const int& val)
{
  return rand() % val * 0.01;
}