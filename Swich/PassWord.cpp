#include "PassWord.h"

PassWord::PassWord(QWidget* parent, QString newTable)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  password = ItemDAO::getInstance()->getPassword(newTable);
  table = newTable;
  QGridLayout* layout = new QGridLayout(this);
  askForPassword(layout);
}

void PassWord::askForPassword(QGridLayout* layout)
{
  QLabel* title = new QLabel(tr("PassWord"), this);
  QLabel* tableDisplay = new QLabel(table, this);
  QLabel* eye = new QLabel("eye", this);
  QRadioButton* button = new QRadioButton(this);
  qlineEdit = new QLineEdit(this);
  invalid = new QLabel(this);
  QPushButton* buttonValidate = new QPushButton(tr("Validate"), this);

  layout->addWidget(title, 0, 0, 1, 3);
  layout->addWidget(tableDisplay, 1, 0);
  layout->addWidget(eye, 1, 1, Qt::AlignRight);
  layout->addWidget(button, 1, 2);
  layout->addWidget(qlineEdit, 2, 0, 1, 3);
  layout->addWidget(invalid, 3, 0, 1, 3);
  layout->addWidget(buttonValidate, 4, 0, 1, 3);

  QRegExp rgx("^[a-z0-9]+");
  QValidator* noSpacesAllowed = new QRegExpValidator(rgx, this);
  qlineEdit->setValidator(noSpacesAllowed);

  button->setChecked(true);

  qlineEdit->setEchoMode(QLineEdit::Password);

  connect(button, SIGNAL(clicked(bool)), this, SLOT(setHideLineEdit(bool)));
  connect(buttonValidate, SIGNAL(clicked()), this, SLOT(validButton()));
}

void PassWord::setHideLineEdit(bool val)
{
  if (val)
  {
    qlineEdit->setEchoMode(QLineEdit::Password);
  }
  else
  {
    qlineEdit->setEchoMode(QLineEdit::Normal);
  }
}

void PassWord::validButton()
{
  if (password != qlineEdit->text())
  {
    invalid->setText(tr("Invalid"));
    return;
  }
  emit transfertValidPassWord(table);
  this->close();
}

PassWord::~PassWord()
{
}
