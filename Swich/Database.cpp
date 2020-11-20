#include "Database.h"

Database::Database(QWidget* parent)
  : QDialog(parent)
{
  QGridLayout* mainLayout = new QGridLayout(this);
  iniDB(mainLayout);

  this->exec();
}

void Database::iniDB(QGridLayout* layout)
{
  ItemDAO::getInstance()->saveToDatabase();
}

Database::~Database()
{
}
