#include "Options.h"

Options::Options(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setMinimumSize(300, 300);

  storedSettings = Utils::loadSettingsFromFile();
  oldSettingsToCompare = storedSettings;
  QGridLayout* layoutOption = new QGridLayout(this);
  ini(layoutOption);

  this->exec();
}

void Options::ini(QGridLayout* layout)
{
  QLabel* langueIcon = new QLabel(this);
  QLabel* langue = new QLabel(tr("Languages"), this);
  QComboBox* langList = new QComboBox(this);
  QLabel* themeIcon = new QLabel(this);
  QLabel* theme = new QLabel(tr("Theme"), this);
  QComboBox* themeList = new QComboBox(this);
  QLabel* fontIcon = new QLabel(this);
  QLabel* font = new QLabel(tr("Font"), this);
  QPushButton* fontChoser = new QPushButton(tr("Selector"), this);
  QPushButton* closeButton = new QPushButton(tr("Close"), this);

  layout->addWidget(langueIcon, 0, 0);
  layout->addWidget(langue, 0, 1);
  layout->addWidget(langList, 1, 0, 1, 3);
  layout->addWidget(themeIcon, 2, 0);
  layout->addWidget(theme, 2, 1);
  layout->addWidget(themeList, 3, 0, 1, 3);
  layout->addWidget(fontIcon, 4, 0);
  layout->addWidget(font, 4, 1);
  layout->addWidget(fontChoser, 4, 2);
  layout->addWidget(closeButton, 5, 0, 1, 3);

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

  layout->setAlignment(Qt::AlignLeft);

  langList->setObjectName("comboLangue");
  themeList->setObjectName("comboTheme");
  fontChoser->setObjectName("fontButton");

  langList->setCursor(Qt::PointingHandCursor);
  themeList->setCursor(Qt::PointingHandCursor);
  fontChoser->setCursor(Qt::PointingHandCursor);
  closeButton->setCursor(Qt::PointingHandCursor);

  SingleData* getData = SingleData::getInstance();
  getData->addLabelToAdaptOnTheme("translations", langueIcon);
  getData->addLabelToAdaptOnTheme("theme", themeIcon);
  getData->addLabelToAdaptOnTheme("letter", fontIcon);

  langueIcon->setPixmap(getData->getPixMapOnActualTheme("translations"));
  themeIcon->setPixmap(getData->getPixMapOnActualTheme("theme"));
  fontIcon->setPixmap(getData->getPixMapOnActualTheme("letter"));
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
  Utils::applyNewFont(storedSettings);
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

  SingleData::getInstance()->setIndexActualTheme(storedSettings.theme);
  Utils::saveSettingsToJsonFile(storedSettings);
}

Options::~Options()
{
}
