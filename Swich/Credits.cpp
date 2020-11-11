#include "Credits.h"

Credits::Credits(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  QHBoxLayout* layout = new QHBoxLayout(this);
  ini(layout);
  this->exec();
}

void Credits::ini(QHBoxLayout* layout)
{
  QLabel* logo = new QLabel(this);
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

  QPixmap pix(":/Swich/SwichLogo.png");
  pix = pix.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  logo->setPixmap(pix);

  layout->addWidget(logo);
  layout->addWidget(text);
}

Credits::~Credits()
{
}
