#include "SingleData.h"

SingleData::SingleData()
{
  listCharacter;
  loadCharacterPix();
}

SingleData* SingleData::instance = 0;

void SingleData::loadCharacterPix()
{

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
}

void SingleData::pushCharacter(const QString& addNom, const QString& pixMap)
{
  QPixmap pix1(pixMap);
  pix1 = pix1.scaled(50, 50, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  listCharacter.push_back(std::pair(addNom, pix1));
}

std::pair<QString, QPixmap> SingleData::getCharacter()
{
  return listCharacter.at(Static::randZeroToVal((int)listCharacter.size()));
}