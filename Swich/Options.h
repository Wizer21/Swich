#pragma once
#include <QObject>
#include "stdafx.h"
#include "Utils.h"
#include "StructSettings.h"

class Options : public QDialog
{
  Q_OBJECT

public:
  Options(QWidget* parent);
  void saveSettings();
  ~Options();

private slots:
  void newFont();
  void setTheme(int index);
  void setTraduction(int index);

private:
  StructSettings::Settings storedSettings;
  StructSettings::Settings oldSettingsToCompare;
  void ini(QVBoxLayout* layout);
  void closeEvent(QCloseEvent* e) override;
};
