#include "CreateNewItem.h"

CreateNewItem::CreateNewItem(QWidget* parent, QString tableUsed)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  tableToAdd = tableUsed;
  QGridLayout* layout = new QGridLayout(this);
  ini(layout);
}

void CreateNewItem::ini(QGridLayout* layout)
{
  QLabel* tableUsed = new QLabel(tr("Add item to ") + tableToAdd, this);
  QLabel* name = new QLabel(tr("Name"), this);
  containName = new QLineEdit(this);
  QLabel* buyp = new QLabel(tr("Buy Price"), this);
  containBuyp = new QLineEdit(this);
  QLabel* sellP = new QLabel(tr("Sell Price"), this);
  containSellP = new QLineEdit(this);
  QPushButton* validation = new QPushButton(tr("Validate"), this);

  layout->addWidget(tableUsed, 0, 0, 1, 2);
  layout->addWidget(name, 1, 0, 1, 2);
  layout->addWidget(containName, 2, 0, 1, 2);
  layout->addWidget(buyp, 3, 0);
  layout->addWidget(containBuyp, 4, 0);
  layout->addWidget(sellP, 3, 1);
  layout->addWidget(containSellP, 4, 1);
  layout->addWidget(validation, 5, 0, 1, 2);

  QRegExp rgx("^[A-Za-z0-9]+");
  QValidator* noSpacesAllowed = new QRegExpValidator(rgx, this);
  containName->setValidator(noSpacesAllowed);

  QRegExp rgxInt("^[0-9]+");
  QValidator* inOnly = new QRegExpValidator(rgxInt, this);
  containBuyp->setValidator(inOnly);
  containSellP->setValidator(inOnly);

  connect(containBuyp, SIGNAL(textEdited(QString)), this, SLOT(updateFromBuyP(QString)));
  connect(containSellP, SIGNAL(textEdited(QString)), this, SLOT(updateFromSellP(QString)));
  connect(validation, SIGNAL(clicked()), this, SLOT(validateButton()));
}

void CreateNewItem::updateFromBuyP(QString value)
{
  containSellP->setText(QString::number(round(value.toInt() * 1.97)));
}

void CreateNewItem::updateFromSellP(QString value)
{
  containBuyp->setText(QString::number(round(value.toInt() / 1.97)));
}

void CreateNewItem::validateButton()
{
  if (containName->text() == "" || containBuyp->text() == "")
  {
    return;
  }

  emit transfertNewItem(tableToAdd, containName->text(), containBuyp->text().toInt(), containSellP->text().toInt() * Utils::randOnlyPositivePercentage(50));
  this->close();
}

CreateNewItem::~CreateNewItem()
{
}
