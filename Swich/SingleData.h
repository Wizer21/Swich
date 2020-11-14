#pragma once
#include "stdafx.h"
#include "Static.h"

class SingleData
{
public:
  static SingleData* getInstance()
  {
    if (!instance)
      instance = new SingleData;
    return instance;
  }
  std::pair<QString, QPixmap> getCharacter();

private:
  SingleData();
  void loadCharacterPix();
  void pushCharacter(const QString& addNom, const QString& pixMap);
  static SingleData* instance;
  std::vector<std::pair<QString, QPixmap>> listCharacter;
};
