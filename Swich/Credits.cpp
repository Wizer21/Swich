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
                   "<p>The developpement started the 02/11/2020 and is avaible on <a href=\"https://github.com/Wizer21/Swich\" style=\"color:#d64b4b\">GitHub</a></p>"
                   "<p>This project was only made through C++ with the Qt library.</p>"
                   "<p>I realized the logo on Photoshop.</p></p>"
                   "<p>Faces picture came from the deep learning generator <a href=\"https://thispersondoesnotexist.com\" style=\"color:#d64b4b\">ThisPersonDoesNotExist</a></p>"
                   "<p>and icons from <a href=\"https://materialdesignicons.com\" style=\"color:#d64b4b\">MaterialDesignIcons</a></p>"),
    this);

  text->setWordWrap(true);
  text->setTextFormat(Qt::RichText);
  text->setTextInteractionFlags(Qt::TextBrowserInteraction);
  text->setOpenExternalLinks(true);
  text->adjustSize();

  SingleData* single = single->getInstance();
  logo->setPixmap(single->getPixmap("creditLogo"));

  layout->addWidget(logo);
  layout->addWidget(text);
}

Credits::~Credits()
{
}
