#include "SingleData.h"

SingleData::SingleData()
{
  loadPixmap();
}

SingleData* SingleData::instance = 0;

void SingleData::loadPixmap()
{
  // Character
  pushCharacter("Frederic", ":/character/Frederic");
  pushCharacter("Francis", ":/character/Francis");
  pushCharacter("Karine", ":/character/Karine");
  pushCharacter("Marie", ":/character/Marie");
  pushCharacter("Camille", ":/character/Camille");
  pushCharacter("Emilie", ":/character/Emilie");
  pushCharacter("Leonie", ":/character/Leonie");
  pushCharacter("Bob", ":/character/Bob");
  pushCharacter("Christophe", ":/character/Christophe");
  pushCharacter("Maxime", ":/character/Maxime");

  // push Soft Pixmap
  pushPixmapToSoft("commercial", ":/Swich/images/briefcase.png", 30, 30);
  pushPixmapToSoft("creditLogo", ":/Swich/images/SwichLogo.png", 200, 200);
  pushPixmapToSoft("factory", ":/Swich/images/factoryBlue.png", 80, 80);

  pushPixmapToSoft("trashlight", ":/icon/images/trashdark.png", 80, 80);
  pushPixmapToSoft("trashdark", ":/icon/images/trashlight.png", 80, 80);
  pushPixmapToSoft("cashlight", ":/icon/images/cashdark.png", 50, 50);
  pushPixmapToSoft("cashdark", ":/icon/images/cashlight.png", 50, 50);
  pushPixmapToSoft("dinolight", ":/icon/images/dinodark.png", 50, 50);
  pushPixmapToSoft("dinodark", ":/icon/images/dinolight.png", 50, 50);
  pushPixmapToSoft("locklight", ":/icon/images/lockdark.png", 50, 50);
  pushPixmapToSoft("lockdark", ":/icon/images/locklight.png", 50, 50);
  pushPixmapToSoft("piecelight", ":/icon/images/piecedark.png", 50, 50);
  pushPixmapToSoft("piecedark", ":/icon/images/piecelight.png", 50, 50);
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

void SingleData::addLabelToAdaptOnFont(const double& multiplier, QLabel* label)
{
  listLabelToAdaptToFont.push_back(std::pair(multiplier, label));
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

  list = (int)listButtonToAdapt.size();

  for (int i = 0; i < list; i++)
  {
    listButtonToAdapt.at(i).second->setIcon(getPixmap(listButtonToAdapt.at(i).first + subName));
  }
}

void SingleData::setFontOnLabels(QFont newFont)
{
  int sizeListFont = (int)listLabelToAdaptToFont.size();
  int currentPixelSize = newFont.pointSize();

  for (int i = 0; i < sizeListFont; i++)
  {
    newFont.setPointSize(currentPixelSize * listLabelToAdaptToFont.at(i).first);
    listLabelToAdaptToFont.at(i).second->setFont(newFont);
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