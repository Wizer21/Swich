#pragma once
#include "stdafx.h"
#include "Static.h"
#include "StructSettings.h"

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
  void addLabelToAdaptOnFont(const double& multiplier, QLabel* label);
  void setColoredIcon(int themeIndex);
  void setFontOnLabels(QFont newFont);
  std::pair<QString, QPixmap> getCharacter();
  QPixmap getPixmap(QString key);
  void deleteButtonOnAdress(QPushButton* button);
  QPixmap getPixMapOnActualTheme(QString key);
  void setIndexActualTheme(int indexTheme);

private:
  int themeActuel;
  SingleData();
  void loadPixmap();
  void pushCharacter(const QString& addNom, const QString& pixMap);
  void pushPixmapToSoft(const QString& key, const QString& url, const int& addWidth, const int& addHeight);

  static SingleData* instance;
  std::vector<std::pair<QString, QPixmap>> listCharacter;
  std::map<QString, QPixmap> listSoftPixmap;
  std::vector<std::pair<QString, QLabel*>> listLabelToAdapt;
  std::vector<std::pair<QString, QPushButton*>> listButtonToAdapt;
  std::vector<std::pair<double, QLabel*>> listLabelToAdaptToFont;
};