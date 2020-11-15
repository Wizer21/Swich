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
  void addLabelToAdaptOnTheme(const QString& key, QLabel* label);
  void addButtoonToAdaptOnTheme(const QString& key, QPushButton* label);
  std::pair<QString, QPixmap> getCharacter();
  QPixmap getPixmap(QString key);
  void setColoredIcon(int themeIndex);

private:
  SingleData();
  void loadPixmap();
  void pushCharacter(const QString& addNom, const QString& pixMap);
  void pushPixmapToSoft(const QString& key, const QString& url, const int& addWidth, const int& addHeight);

  static SingleData* instance;
  std::vector<std::pair<QString, QPixmap>> listCharacter;
  std::map<QString, QPixmap> listSoftPixmap;
  std::vector<std::pair<QString, QLabel*>> listLabelToAdapt;
  std::vector<std::pair<QString, QPushButton*>> listButtonToAdapt;
};
