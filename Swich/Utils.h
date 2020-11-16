#pragma once
#include "stdafx.h"
#include "StructSettings.h"
#include "SingleData.h"

class Utils : public QObject
{
  Q_OBJECT

public:
  static StructSettings::Settings loadSettingsFromFile();
  static void saveSettingsToJsonFile(StructSettings::Settings getSettings);

  static void applyNewTheme(int index);
  static void applyNewLanguage(int index);
  static void applyNewFont(StructSettings::Settings getStruct);

private:
  Utils();
};
