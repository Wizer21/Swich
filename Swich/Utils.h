#pragma once
#include "stdafx.h"
#include "StructSettings.h"
#include "SingleData.h"
#include <random>

class Utils : public QObject
{
  Q_OBJECT

public:
  static StructSettings::Settings loadSettingsFromFile();
  static void saveSettingsToJsonFile(StructSettings::Settings getSettings);
  static int randZeroToVal(const int& val);
  static double randNegativeIntToPercentage(const int& val);
  static double randOnlyPositivePercentage(const int& val);

  static void applyNewTheme(int index);
  static void applyNewLanguage(int index);
  static void applyNewFont(StructSettings::Settings getStruct);

private:
  Utils();
};
