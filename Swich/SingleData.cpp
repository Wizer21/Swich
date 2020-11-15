#include "SingleData.h"

SingleData::SingleData()
{
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
  pushPixmapToSoft("factory", ":/Swich/factoryBlue.png", 80, 80);

  pushPixmapToSoft("trashlight", ":/Swich/trashdark.png", 80, 80);
  pushPixmapToSoft("trashdark", ":/Swich/trashlight.png", 80, 80);
  pushPixmapToSoft("cashlight", ":/Swich/cashdark.png", 50, 50);
  pushPixmapToSoft("cashdark", ":/Swich/cashlight.png", 50, 50);
  pushPixmapToSoft("dinolight", ":/Swich/dinodark.png", 50, 50);
  pushPixmapToSoft("dinodark", ":/Swich/dinolight.png", 50, 50);
  pushPixmapToSoft("locklight", ":/Swich/lockdark.png", 50, 50);
  pushPixmapToSoft("lockdark", ":/Swich/locklight.png", 50, 50);
  pushPixmapToSoft("piecelight", ":/Swich/piecedark.png", 50, 50);
  pushPixmapToSoft("piecedark", ":/Swich/piecelight.png", 50, 50);
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

void SingleData::addLabelToAdaptOnTheme(const QString& key, QLabel* label)
{
  listLabelToAdapt.push_back(std::pair(key, label));
}
void SingleData::addButtoonToAdaptOnTheme(const QString& key, QPushButton* button)
{
  listButtonToAdapt.push_back(std::pair(key, button));
}

void SingleData::setColoredIcon(int themeIndex)
{
  int list = listLabelToAdapt.size();
  QString subName = "";

  if (themeIndex == 0)
  {
    subName = "light";
  }
  else if (themeIndex == 1)
  {
    subName = "dark";
  }

  for (int i = 0; i < list; i++)
  {
    listLabelToAdapt.at(i).second->setPixmap(getPixmap(listLabelToAdapt.at(i).first + subName));
  }

  list = listButtonToAdapt.size();

  for (int i = 0; i < list; i++)
  {
    listButtonToAdapt.at(i).second->setIcon(getPixmap(listButtonToAdapt.at(i).first + subName));
  }
}

std::pair<QString, QPixmap> SingleData::getCharacter()
{
  return listCharacter.at(Static::randZeroToVal((int)listCharacter.size()));
}

QPixmap SingleData::getPixmap(QString key)
{
  return listSoftPixmap.at(key);
}