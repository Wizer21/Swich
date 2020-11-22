#include "NewTable.h"

NewTable::NewTable(QWidget* parent)
  : QDialog(parent)
{
  QGridLayout* layout = new QGridLayout(this);
  ini(layout);
}

void NewTable::ini(QGridLayout* layout)
{
  QLabel* title = new QLabel(tr("New Table"), this);
  QLabel* name = new QLabel(tr("Table Name *"), this);
  containName = new QLineEdit(this);
  QLabel* passWord = new QLabel(tr("PassWord"), this);
  containPassword = new QLineEdit(this);
  errorMessage = new QLabel(this);
  QPushButton* valider = new QPushButton(tr("Validate"), this);

  layout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);

  layout->addWidget(name, 1, 0, 1, 2);
  layout->addWidget(containName, 2, 0, 1, 2);
  layout->addWidget(passWord, 3, 0, 1, 2);
  layout->addWidget(containPassword, 4, 0, 1, 2);
  layout->addWidget(errorMessage, 5, 0, 1, 2);
  layout->addWidget(valider, 6, 0, 1, 2);

  QRegExp rgx("^[a-z0-9]+");
  QValidator* noSpacesAllowed = new QRegExpValidator(rgx, this);

  containName->setValidator(noSpacesAllowed);
  containPassword->setValidator(noSpacesAllowed);

  containName->setMaxLength(12);

  connect(valider, SIGNAL(clicked()), this, SLOT(validatePressed()));
}

void NewTable::validatePressed()
{
  QString containNewName = containName->text();
  if (containNewName == "")
  {
    errorMessage->setText(tr("Table name is empty."));
    return;
  }
  else
  {
    QStringList tableList = ItemDAO::getInstance()->getTablesList();
    int sizeList = (int)tableList.size();
    QString lowerEnterVer = containNewName.toLower();

    for (int i = 0; i < sizeList; i++)
    {
      if (tableList.at(i).toLower() == containNewName.toLower())
      {
        errorMessage->setText(tr("This table already exist."));
        return;
      };
    }
  }
  emit transfertNewTable(containNewName, containPassword->text());
  this->close();
}

NewTable::~NewTable()
{
}
