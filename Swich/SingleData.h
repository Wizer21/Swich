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
  QPixmap getPixmap(QString key);

private:
  SingleData();
  void loadPixmap();
  void pushCharacter(const QString& addNom, const QString& pixMap);
  void pushPixmapToSoft(const QString& key, const QString& url, const int& addWidth, const int& addHeight);
  static SingleData* instance;
  std::vector<std::pair<QString, QPixmap>> listCharacter;
  std::map<QString, QPixmap> listSoftPixmap;
};
