#include "Options.h"

Options::Options(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->setMinimumSize(300, 300);
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
  connect(themeList, SIGNAL(activated(int)), this, SLOT(setTheme(int)));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
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
  QFile lightQSSFile(":/Swich/dark.qss");
  QFile darkQSSFile(":/Swich/dark.qss");

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
}

Options::~Options()
{
}
