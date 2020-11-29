#include "Utils.h"

Utils::Utils()
{
}

StructSettings::Settings Utils::loadSettingsFromFile()
{
  checkSettingsFileExistence();
  QFile lSettingsFile(QCoreApplication::applicationDirPath() + QDir::separator() + "config.json");
  lSettingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
  QString lSettingsData = lSettingsFile.readAll();
  lSettingsFile.close();

  QJsonDocument lJsonDocument(QJsonDocument::fromJson(lSettingsData.toUtf8()));
  QJsonObject lSettingsJSON = lJsonDocument.object();

  StructSettings::Settings getSettings;

  if (lSettingsJSON.contains("langue") && lSettingsJSON["langue"].isDouble())
  {
    getSettings.langue = lSettingsJSON["langue"].toInt();
  }
  if (lSettingsJSON.contains("theme") && lSettingsJSON["theme"].isDouble())
  {
    getSettings.theme = lSettingsJSON["theme"].toInt();
  }
  if (lSettingsJSON.contains("font_family") && lSettingsJSON["font_family"].isString())
  {
    getSettings.font_family = lSettingsJSON["font_family"].toString();
  }
  if (lSettingsJSON.contains("font_style") && lSettingsJSON["font_style"].isString())
  {
    getSettings.font_style = lSettingsJSON["font_style"].toString();
  }
  if (lSettingsJSON.contains("font_size") && lSettingsJSON["font_size"].isDouble())
  {
    getSettings.font_size = lSettingsJSON["font_size"].toInt();
  }
  if (lSettingsJSON.contains("font_weight") && lSettingsJSON["font_weight"].isDouble())
  {
    getSettings.font_weight = lSettingsJSON["font_weight"].toInt();
  }
  if (lSettingsJSON.contains("font_italic") && lSettingsJSON["font_italic"].isBool())
  {
    getSettings.font_italic = lSettingsJSON["font_italic"].toBool();
  }
  if (lSettingsJSON.contains("font_underline") && lSettingsJSON["font_underline"].isBool())
  {
    getSettings.font_underline = lSettingsJSON["font_underline"].toBool();
  }
  if (lSettingsJSON.contains("font_strike_out") && lSettingsJSON["font_strike_out"].isBool())
  {
    getSettings.font_strike_out = lSettingsJSON["font_strike_out"].toBool();
  }
  return getSettings;
}

void Utils::saveSettingsToJsonFile(StructSettings::Settings getSettings)
{
  QJsonObject objJson;
  objJson["langue"] = getSettings.langue;
  objJson["theme"] = getSettings.theme;

  objJson["font_family"] = getSettings.font_family;
  objJson["font_style"] = getSettings.font_style;
  objJson["font_size"] = getSettings.font_size;
  objJson["font_weight"] = getSettings.font_weight;
  objJson["font_italic"] = getSettings.font_italic;
  objJson["font_underline"] = getSettings.font_underline;
  objJson["font_strike_out"] = getSettings.font_strike_out;

  QFile lSettingsFile(QCoreApplication::applicationDirPath() + QDir::separator() + "config.json");
  lSettingsFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

  QJsonDocument saveDoc(objJson);
  lSettingsFile.write(saveDoc.toJson());

  lSettingsFile.close();
}

void Utils::applyNewTheme(int index)
{
  QFile lightQSSFile(":/Swich/qss/light.qss");
  QFile darkQSSFile(":/Swich/qss/dark.qss");

  switch (index)
  {
    case 0:
      if (lightQSSFile.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        QTextStream lStream(&lightQSSFile);
        qApp->setStyleSheet(lStream.readAll());
        lightQSSFile.close();
      }
      break;
    case 1:
      if (darkQSSFile.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        QTextStream lStream(&darkQSSFile);
        qApp->setStyleSheet(lStream.readAll());
        darkQSSFile.close();
      }
      break;
    default:
      break;
  }

  SingleData::getInstance()->setColoredIcon(index);
}

void Utils::applyNewLanguage(int index)
{
  QString langueToSet = "";

  switch (index)
  {
    case 0:
      langueToSet = "fr";
      break;
    case 1:
      langueToSet = "en";
      break;
    default:
      langueToSet = "en";
      return;
  }

  auto lTranslator{new QTranslator()};
  if (lTranslator->load(QString(":/Swich/translations/swich_%1.qm").arg(langueToSet)))
  {
    qApp->installTranslator(lTranslator);
  }

  auto lQtBaseTranslator{new QTranslator()};
  if (lQtBaseTranslator->load("qt_" + langueToSet + ".qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
  {
    qApp->installTranslator(lQtBaseTranslator);
  }
}

void Utils::applyNewFont(StructSettings::Settings getStruct)
{
  QFont newWonft;
  newWonft.setFamily(getStruct.font_family);
  newWonft.setStyleName(getStruct.font_style);
  newWonft.setPointSize(getStruct.font_size);
  newWonft.setWeight(getStruct.font_weight);
  newWonft.setItalic(getStruct.font_italic);
  newWonft.setUnderline(getStruct.font_underline);
  newWonft.setStrikeOut(getStruct.font_strike_out);

  newWonft.setStyleStrategy(QFont::PreferAntialias);

  SingleData::getInstance()->setFontOnLabels(newWonft);
  qApp->setFont(newWonft);

  SingleData::getInstance()->setFontOnLabels(newWonft);
}

void Utils::checkSettingsFileExistence()
{
  auto lSettingsFilePath{QCoreApplication::applicationDirPath() + QDir::separator() + "config.json"};
  if (!QFile(lSettingsFilePath).exists())
  {
    StructSettings::Settings lSettings;
    Utils::saveSettingsToJsonFile(lSettings);
  }
}

// RAND --
int Utils::randZeroToVal(int val)
{
  if (val != 0)
  {
    val -= 1;
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  std::uniform_int_distribution<int> randval(0, val);
  return randval(generator);
}

double Utils::randNegativeIntToPercentage(const int& val)
{
  return (randZeroToVal(val) - randZeroToVal(val) * 2) * 0.01;
}

double Utils::randOnlyPositivePercentage(const int& val)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> randval(0, val - 1);
  return randval(generator) * 0.01;
}

QString Utils::getThemeOnActualWidget(int currentId)
{
  int currentTheme = SingleData::getInstance()->getThemeActuel();

  if (currentTheme == 0 || currentTheme == 1)
  {
    //List soft colors
    switch (currentId)
    {
      case 0:
        return "#ff5252";
        break;
      case 1:
        return "#7c4dff";
        break;
      case 2:
        return "#536dfe";
        break;
      case 3:
        return "#64ffda";
        break;
      case 4:
        return "#b2ff59";
        break;
      case 5:
        return "#ffd740";
        break;
      case 6:
        return "#ff6e40";
        break;
      default:
        return "";
        break;
    }
  }
  return "";
  //List vibrant colors
}