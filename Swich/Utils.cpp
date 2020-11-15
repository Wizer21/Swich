#include "Utils.h"

Utils::Utils()
{
}

StructSettings::Settings Utils::loadSettingsFromFile()
{

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
  return getSettings;
}

void Utils::saveSettingsToJsonFile(StructSettings::Settings getSettings)
{
  QJsonObject objJson;
  objJson["langue"] = getSettings.langue;
  objJson["theme"] = getSettings.theme;

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
