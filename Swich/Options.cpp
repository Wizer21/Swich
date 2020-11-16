#include "Options.h"

Options::Options(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setMinimumSize(300, 300);

  storedSettings = Utils::loadSettingsFromFile();
  oldSettingsToCompare = storedSettings;
  QVBoxLayout* layoutOption = new QVBoxLayout(this);
  ini(layoutOption);

  this->exec();
}

void Options::ini(QVBoxLayout* layout)
{
  QLabel* langue = new QLabel(tr("Languages"), this);
  QComboBox* langList = new QComboBox(this);
  QLabel* theme = new QLabel(tr("Theme"), this);
  QComboBox* themeList = new QComboBox(this);
  QLabel* font = new QLabel(tr("Font"), this);
  QPushButton* fontChoser = new QPushButton(tr("Font choser"), this);
  QPushButton* closeButton = new QPushButton(tr("Close"), this);

  layout->addWidget(langue);
  layout->addWidget(langList);
  layout->addWidget(theme);
  layout->addWidget(themeList);
  layout->addWidget(font);
  layout->addWidget(fontChoser);
  layout->addWidget(closeButton);

  langList->addItem("Francais");
  langList->addItem("English");
  themeList->addItem(tr("Light"));
  themeList->addItem(tr("Dark"));

  connect(fontChoser, SIGNAL(clicked()), this, SLOT(newFont()));
  connect(langList, SIGNAL(activated(int)), this, SLOT(setTraduction(int)));
  connect(themeList, SIGNAL(activated(int)), this, SLOT(setTheme(int)));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  themeList->setCurrentIndex(storedSettings.theme);
  langList->setCurrentIndex(storedSettings.langue);

  langList->setItemDelegate(new QStyledItemDelegate());
  themeList->setItemDelegate(new QStyledItemDelegate());
}

void Options::newFont()
{
  bool validButton = true;
  QFont font = QFontDialog::getFont(&validButton, qApp->font(), this);
  if (!validButton)
  {
    return;
  }
  storedSettings.font_family = font.family();
  storedSettings.font_style = font.styleName();
  storedSettings.font_size = font.pointSize();
  storedSettings.font_weight = font.weight();
  storedSettings.font_italic = font.italic();
  storedSettings.font_underline = font.underline();
  storedSettings.font_strike_out = font.strikeOut();

  Utils::applyNewFont(storedSettings);
}

void Options::setTheme(int index)
{
  storedSettings.theme = index;
  Utils::applyNewTheme(index);
}

void Options::setTraduction(int index)
{
  storedSettings.langue = index;
  Utils::applyNewLanguage(index);
}

void Options::closeEvent(QCloseEvent* e)
{
  if (storedSettings != oldSettingsToCompare)
  {
    QMessageBox lMessageBox(QMessageBox::Icon::Information, tr("Info"), tr("The application needs to be restarted."), QMessageBox::StandardButton::Ok);
    lMessageBox.exec();
  }
  Utils::saveSettingsToJsonFile(storedSettings);
}

Options::~Options()
{
}
