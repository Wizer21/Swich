#include "Database.h"

Database::Database(QWidget* parent)
  : QDialog(parent)
{
  QGridLayout* mainLayout = new QGridLayout(this);
  iniDB(mainLayout);
  loadTableList();

  this->resize(600, 400);
  this->exec();
}

void Database::iniDB(QGridLayout* layout)
{
  runningTable = new QLabel("nameTable", this);
  QLabel* dataOn_Off = new QLabel("on", this);
  QLabel* iconOn_Off = new QLabel("logo", this);

  QScrollArea* containTableList = new QScrollArea(this);
  QWidget* widgetScroll = new QWidget(this);
  layoutInScrollArea = new QVBoxLayout(this);

  widgetStack = new QStackedWidget(this);
  QPushButton* addTable = new QPushButton(tr("NewTable"));

  layout->addWidget(runningTable, 0, 0, 1, 2);
  layout->addWidget(dataOn_Off, 0, 2, Qt::AlignRight);
  layout->addWidget(iconOn_Off, 0, 3, Qt::AlignRight);
  layout->addWidget(containTableList, 1, 0);
  containTableList->setWidget(widgetScroll);
  widgetScroll->setLayout(layoutInScrollArea);
  layout->addWidget(addTable, 2, 0);
  layout->addWidget(widgetStack, 1, 1, 2, 3);

  layoutInScrollArea->setAlignment(Qt::AlignTop);
  containTableList->setMaximumWidth(this->width() * 1.4);
  containTableList->setWidgetResizable(true);
};

void Database::loadTableList()
{
  QStringList tableList = ItemDAO::getInstance()->getTablesList();
  int sizeList = (int)tableList.size();
  for (int i = 0; i < sizeList; i++)
  {
    QPushButton* buttonTable = new QPushButton(tableList.at(i), this);
    layoutInScrollArea->addWidget(buttonTable);
    createTableWidgets(tableList.at(i));

    buttonTable->setObjectName(QString::number(i));
    connect(buttonTable, SIGNAL(clicked()), this, SLOT(setWidgetToDisplay()));
  }
}

void Database::createTableWidgets(QString tableName)
{
  QWidget* mainTableWidget = new QWidget(this);
  QGridLayout* mainLayoutTable = new QGridLayout(this);
  QLabel* displayTableName = new QLabel(tableName, this);
  QPushButton* loadDB = new QPushButton("load", this);
  QPushButton* deleteDB = new QPushButton("deleteDB", this);
  QPushButton* addItem = new QPushButton("addItem", this);
  QPushButton* deleteItem = new QPushButton("deleteItem", this);
  QTableView* displayTable = new QTableView(this);

  widgetStack->addWidget(mainTableWidget);
  mainTableWidget->setLayout(mainLayoutTable);
  mainLayoutTable->addWidget(displayTableName, 0, 0, 2, 3);
  mainLayoutTable->addWidget(loadDB, 0, 3);
  mainLayoutTable->addWidget(deleteDB, 1, 3);
  mainLayoutTable->addWidget(addItem, 2, 0, 1, 2);
  mainLayoutTable->addWidget(deleteItem, 2, 2, 1, 2);
  mainLayoutTable->addWidget(displayTable, 3, 0, 1, 4);

  loadDB->setObjectName(tableName);
  displayTable->setModel(ItemDAO::getInstance()->getQuerryModel(tableName));
  displayTable->show();

  displayTable->resizeColumnsToContents();
  connect(loadDB, SIGNAL(clicked()), this, SLOT(loadNewTable()));
}

void Database::setWidgetToDisplay()
{
  widgetStack->setCurrentIndex(sender()->objectName().toInt());
}

void Database::loadNewTable()
{
  QString newTableName = sender()->objectName();
  ItemDAO::getInstance()->loadDBToItemList(newTableName);
  runningTable->setText(newTableName);
}

Database::~Database()
{
}
