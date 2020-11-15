#pragma once
#include "stdafx.h"
#include "StructSettings.h"

class Utils : public QObject
{
  Q_OBJECT

public:
  static StructSettings::Settings loadSettingsFromFile();
  static void saveSettingsToJsonFile(StructSettings::Settings getSettings);

  static void applyNewTheme(int index);
  static void applyNewLanguage(int index);

private:
  Utils();
};
