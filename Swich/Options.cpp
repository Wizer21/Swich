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
  font.setStyleStrategy(QFont::PreferAntialias);
  qApp->setFont(font);
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
  if (storedSettings.langue != oldSettingsToCompare.langue)
  {
    QMessageBox lMessageBox(QMessageBox::Icon::Information, tr("Info"), tr("The application needs to be restarted."), QMessageBox::StandardButton::Ok);
    lMessageBox.exec();
  }
  Utils::saveSettingsToJsonFile(storedSettings);
}

Options::~Options()
{
}
