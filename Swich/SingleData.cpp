#include "SingleData.h"

SingleData::SingleData()
{
  loadPixmap();
  themeActuel = 0;
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
  pushPixmapToSoft("creditLogo", ":/Swich/images/SwichLogo.png", 400, 400);
  pushPixmapToSoft("factory", ":/Swich/images/factoryBlue.png", 80, 80);
  pushPixmapToSoft("notification", ":/icon/images/notification.png", 50, 50);
  pushPixmapToSoft("onCircle", ":/Swich/images/onCircle.png", 30, 30);
  pushPixmapToSoft("offCircle", ":/Swich/images/offCircle.png", 30, 30);
  pushPixmapToSoft("downloaddark", ":/icon/images/downloaddark.png", 50, 50);
  pushPixmapToSoft("piecedark", ":/icon/images/piecelight.png", 50, 50);
  pushPixmapToSoft("piecelight", ":/icon/images/piecedark.png", 50, 50);

  pushPixmapToSoft("trashlight", ":/icon/images/trashdark.png", 80, 80);
  pushPixmapToSoft("trashdark", ":/icon/images/trashlight.png", 80, 80);
  pushPixmapToSoft("cashlight", ":/icon/images/cashdark.png", 50, 50);
  pushPixmapToSoft("cashdark", ":/icon/images/cashlight.png", 50, 50);
  pushPixmapToSoft("dinolight", ":/icon/images/dinodark.png", 50, 50);
  pushPixmapToSoft("dinodark", ":/icon/images/dinolight.png", 50, 50);
  pushPixmapToSoft("locklight", ":/icon/images/lockdark.png", 50, 50);
  pushPixmapToSoft("lockdark", ":/icon/images/locklight.png", 50, 50);
  pushPixmapToSoft("eyelight", ":/icon/images/eyedark.png", 50, 50);
  pushPixmapToSoft("eyedark", ":/icon/images/eyelight.png", 50, 50);

  pushPixmapToSoft("closeeyedark", ":/icon/images/closeeyelight.png", 50, 50);
  pushPixmapToSoft("databasedark", ":/icon/images/databaselight.png", 50, 50);
  pushPixmapToSoft("itemdeletedark", ":/icon/images/itemdeletelight.png", 50, 50);
  pushPixmapToSoft("itemdark", ":/icon/images/itemlight.png", 50, 50);
  pushPixmapToSoft("letterdark", ":/icon/images/letterlight.png", 40, 40);
  pushPixmapToSoft("nextdark", ":/icon/images/nextlight.png", 50, 50);
  pushPixmapToSoft("settingsdark", ":/icon/images/settingslight.png", 50, 50);
  pushPixmapToSoft("tabledark", ":/icon/images/tablelight.png", 50, 50);
  pushPixmapToSoft("themedark", ":/icon/images/themelight.png", 40, 40);
  pushPixmapToSoft("translationsdark", ":/icon/images/translationslight.png", 40, 40);
  pushPixmapToSoft("tutorialdark", ":/icon/images/tutoriallight.png", 50, 50);
  pushPixmapToSoft("uploaddark", ":/icon/images/uploadlight.png", 50, 50);
  pushPixmapToSoft("closedark", ":/icon/images/closelight.png", 50, 50);
  pushPixmapToSoft("trophydark", ":/icon/images/trophylight.png", 40, 40);

  pushPixmapToSoft("closeeyelight", ":/icon/images/closeeyedark.png", 50, 50);
  pushPixmapToSoft("databaselight", ":/icon/images/databasedark.png", 50, 50);
  pushPixmapToSoft("itemdeletelight", ":/icon/images/itemdeletedark.png", 50, 50);
  pushPixmapToSoft("itemlight", ":/icon/images/itemdark.png", 50, 50);
  pushPixmapToSoft("letterlight", ":/icon/images/letterdark.png", 40, 40);
  pushPixmapToSoft("nextlight", ":/icon/images/nextdark.png", 50, 50);
  pushPixmapToSoft("settingslight", ":/icon/images/settingsdark.png", 50, 50);
  pushPixmapToSoft("tablelight", ":/icon/images/tabledark.png", 50, 50);
  pushPixmapToSoft("themelight", ":/icon/images/themedark.png", 40, 40);
  pushPixmapToSoft("translationslight", ":/icon/images/translationsdark.png", 40, 40);
  pushPixmapToSoft("tutoriallight", ":/icon/images/tutorialdark.png", 50, 50);
  pushPixmapToSoft("uploadlight", ":/icon/images/uploaddark.png", 50, 50);
  pushPixmapToSoft("closelight", ":/icon/images/closedark.png", 50, 50);
  pushPixmapToSoft("trophylight", ":/icon/images/trophydark.png", 40, 40);
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
void SingleData::addActionToAdaptOnTheme(const QString& key, QAction* action)
{
  listActionToAdapt.push_back(std::pair(key, action));
}

void SingleData::addLabelToAdaptOnFont(const double& multiplier, QLabel* label)
{
  listLabelToAdaptToFont.push_back(std::pair(multiplier, label));
}

void SingleData::setColoredIcon(int themeIndex)
{
  QString subName = "";

  if (themeIndex == 0)
  {
    subName = "light";
  }
  else if (themeIndex == 1)
  {
    subName = "dark";
  }

  int sizeList = (int)listLabelToAdapt.size();
  for (int i = 0; i < sizeList; i++)
  {
    listLabelToAdapt.at(i).second->setPixmap(getPixmap(listLabelToAdapt.at(i).first + subName));
  }

  sizeList = (int)listButtonToAdapt.size();
  for (int i = 0; i < sizeList; i++)
  {
    listButtonToAdapt.at(i).second->setIcon(getPixmap(listButtonToAdapt.at(i).first + subName));
  }

  sizeList = (int)listActionToAdapt.size();
  for (int i = 0; i < sizeList; i++)
  {
    listActionToAdapt.at(i).second->setIcon(getPixmap(listActionToAdapt.at(i).first + subName));
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
  return listCharacter.at(Utils::randZeroToVal((int)listCharacter.size()));
}

QPixmap SingleData::getPixmap(QString key)
{
  return listSoftPixmap.at(key);
}

QPixmap SingleData::getPixMapOnActualTheme(QString key)
{
  QString subKey = "";

  switch (themeActuel)
  {
    case 0:
      subKey = "light";
      break;
    case 1:
      subKey = "dark";
      break;
  }

  return getPixmap(key + subKey);
}

int SingleData::getThemeActuel()
{
  return themeActuel;
}

void SingleData::setIndexActualTheme(int indexTheme)
{
  themeActuel = indexTheme;
}

void SingleData::deleteButtonOnAdress(QPushButton* button)
{
  int sizeList = (int)listButtonToAdapt.size();
  for (int i = 0; i < sizeList; i++)
  {
    if (listButtonToAdapt.at(i).second == button)
    {
      listButtonToAdapt.erase(listButtonToAdapt.begin() + i);
      return;
    }
  }
}