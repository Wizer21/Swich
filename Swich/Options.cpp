#include "Options.h"

Options::Options(QWidget* parent)
  : QDialog(parent)
{
  QVBoxLayout* layoutOption = new QVBoxLayout(this);
  ini(layoutOption);
}

void Options::ini(QVBoxLayout* layout)
{
  QLabel* langue = new QLabel(tr("Languages"), this);
  QComboBox* langList = new QComboBox(this);
  QLabel* theme = new QLabel(tr("Theme"), this);
  QComboBox* themeList = new QComboBox(this);
  QLabel* font = new QLabel(tr("Font"), this);
  QPushButton* fontChoser = new QPushButton(tr("Font choser"), this);

  layout->addWidget(langue);
  layout->addWidget(langList);
  layout->addWidget(theme);
  layout->addWidget(themeList);
  layout->addWidget(font);
  layout->addWidget(fontChoser);

  langList->addItem("Francais");
  langList->addItem("English");
  themeList->addItem("Light");
  themeList->addItem("Dark");

  connect(fontChoser, SIGNAL(clicked()), this, SLOT(newFont()));
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

Options::~Options()
{
}
