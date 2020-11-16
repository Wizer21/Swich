#pragma once
#include "stdafx.h"

namespace StructSettings
{
  struct Settings
  {
  public:
    int langue = 0;
    int theme = 0;

    QString font_family = "";
    QString font_style = "";
    int font_size = 0;
    int font_weight = 0;
    bool font_italic = false;
    bool font_underline = false;
    bool font_strike_out = false;

    bool operator==(const StructSettings::Settings& settingsToCompare)
    {
      return (
        this->langue == settingsToCompare.langue
        && this->theme == settingsToCompare.theme
        && this->font_family == settingsToCompare.font_family
        && this->font_style == settingsToCompare.font_style
        && this->font_size == settingsToCompare.font_size
        && this->font_weight == settingsToCompare.font_weight
        && this->font_italic == settingsToCompare.font_italic
        && this->font_underline == settingsToCompare.font_underline
        && this->font_strike_out == settingsToCompare.font_strike_out);
    }

    bool operator!=(const StructSettings::Settings& settingsToCompare)
    {
      return (
        this->langue != settingsToCompare.langue
        || this->theme != settingsToCompare.theme
        || this->font_family != settingsToCompare.font_family
        || this->font_style != settingsToCompare.font_style
        || this->font_size != settingsToCompare.font_size
        || this->font_weight != settingsToCompare.font_weight
        || this->font_italic != settingsToCompare.font_italic
        || this->font_underline != settingsToCompare.font_underline
        || this->font_strike_out != settingsToCompare.font_strike_out);
    }
  };

};