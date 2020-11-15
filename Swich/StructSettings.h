#pragma once

namespace StructSettings
{
  struct Settings
  {
  public:
    int langue = 0;
    int theme = 0;

    bool operator==(const StructSettings::Settings& settingsToCompare)
    {
      return (
        this->langue == settingsToCompare.langue && this->theme == settingsToCompare.theme);
    }

    bool operator!=(const StructSettings::Settings& settingsToCompare)
    {
      return (
        this->langue != settingsToCompare.langue || this->theme != settingsToCompare.theme);
    }
  };
};