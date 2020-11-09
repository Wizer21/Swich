#include "Credits.h"

Credits::Credits(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  QVBoxLayout* layout = new QVBoxLayout(this);
  ini(layout);
}

void Credits::ini(QVBoxLayout* layout)
{
  QLabel* text = new QLabel(
    QStringLiteral("<h1>This project</h1>"
                   "<p>This project was mainly made to showcase my skills and keep an history of my progression.</p>"
                   "<p>The developpement started the 02/11/2020 and is avaible on <a href=\"https://github.com/Wizer21/Swich\">GitHub</a></p>"
                   "<p>This project was only made through C++ with the Qt library.</p>"
                   "<p>I realized the logo on Photoshop.</p>"),
    this);

  text->setWordWrap(true);
  text->setTextFormat(Qt::RichText);
  text->setTextInteractionFlags(Qt::TextBrowserInteraction);
  text->setOpenExternalLinks(true);
  text->adjustSize();
  layout->addWidget(text);
}

Credits::~Credits()
{
}
