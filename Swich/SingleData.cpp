#include "SingleData.h"

SingleData::SingleData()
{
  listCharacter;
  listSoftPixmap;
  loadPixmap();
}

SingleData* SingleData::instance = 0;

void SingleData::loadPixmap()
{
  // Character
  pushCharacter("Frederic", ":/Swich/Frederic.jpg");
  pushCharacter("Francis", ":/Swich/Francis.jpg");
  pushCharacter("Karine", ":/Swich/Karine.jpg");
  pushCharacter("Marie", ":/Swich/Marie.jpg");
  pushCharacter("Camille", ":/Swich/Camille.jpg");
  pushCharacter("Emilie", ":/Swich/Emilie.jpg");
  pushCharacter("Leonie", ":/Swich/Leonie.jpg");
  pushCharacter("Bob", ":/Swich/Bob.jpg");
  pushCharacter("Christophe", ":/Swich/Christophe.jpg");
  pushCharacter("Maxime", ":/Swich/Maxime.jpg");

  // push Soft Pixmap
  pushPixmapToSoft("commercial", ":/Swich/briefcase.png", 20, 20);
  pushPixmapToSoft("creditLogo", ":/Swich/SwichLogo.png", 200, 200);
  pushPixmapToSoft("trash", ":/Swich/trash-can-outline.png", 80, 80);
}

void SingleData::pushCharacter(const QString& addNom, const QString& pixMap)
{
  QPixmap pix1(pixMap);
  pix1 = pix1.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  listSoftPixmap.insert(std::pair<QString, QPixmap>(addNom, pix1));
  listCharacter.push_back(std::pair(addNom, pix1));
}

void SingleData::pushPixmapToSoft(const QString& key, const QString& url, const int& addWidth, const int& addHeight)
{
  QPixmap newPix(url);
  newPix = newPix.scaled(addWidth, addHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  listSoftPixmap.insert(std::pair<QString, QPixmap>(key, newPix));
}

std::pair<QString, QPixmap> SingleData::getCharacter()
{
  return listCharacter.at(Static::randZeroToVal((int)listCharacter.size()));
}

QPixmap SingleData::getPixmap(QString key)
{
  return listSoftPixmap.at(key);
}