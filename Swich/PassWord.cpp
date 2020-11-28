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
  buttonEye = new QPushButton(this);
  qlineEdit = new QLineEdit(this);
  invalid = new QLabel(this);
  QPushButton* buttonValidate = new QPushButton(tr("Validate"), this);

  layout->addWidget(title, 0, 0, 1, 3);
  layout->addWidget(tableDisplay, 1, 0, 1, 3);
  layout->addWidget(qlineEdit, 2, 0, 1, 2);
  layout->addWidget(buttonEye, 2, 2, 1, 1);
  layout->addWidget(invalid, 3, 0, 1, 3);
  layout->addWidget(buttonValidate, 4, 0, 1, 3);

  QRegExp rgx("^[a-z0-9]+");
  QValidator* noSpacesAllowed = new QRegExpValidator(rgx, this);
  qlineEdit->setValidator(noSpacesAllowed);

  buttonEye->setIcon(SingleData::getInstance()->getPixMapOnActualTheme("closeeye"));
  buttonEye->setStyleSheet("QPushButton{border: 0px solid white;background-color: transparent;}");

  buttonEye->setCursor(Qt::PointingHandCursor);
  buttonValidate->setCursor(Qt::PointingHandCursor);
  qlineEdit->setEchoMode(QLineEdit::Password);

  QFont font = qApp->font();
  font.setPointSize(font.pointSize() * 1.5);
  title->setFont(font);

  connect(buttonEye, SIGNAL(pressed()), this, SLOT(eyeClicked()));
  connect(buttonEye, SIGNAL(released()), this, SLOT(eyeReleased()));
  connect(buttonValidate, SIGNAL(clicked()), this, SLOT(validButton()));
}

void PassWord::eyeClicked()
{
  buttonEye->setIcon(SingleData::getInstance()->getPixMapOnActualTheme("eye"));
  qlineEdit->setEchoMode(QLineEdit::Normal);
}

void PassWord::eyeReleased()
{
  buttonEye->setIcon(SingleData::getInstance()->getPixMapOnActualTheme("closeeye"));
  qlineEdit->setEchoMode(QLineEdit::Password);
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
