#include "Database.h"

Database::Database(QWidget* parent)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);

  QGridLayout* mainLayout = new QGridLayout(this);
  iniDB(mainLayout);

  this->resize(700, 450);
  this->exec();
}

void Database::iniDB(QGridLayout* layout)
{
  runningTable = new QLabel("nameTable", this);

  QWidget* containStatu = new QWidget(this);
  QHBoxLayout* layoutStatu = new QHBoxLayout(this);
  QLabel* dataOn_Off = new QLabel(this);
  QLabel* iconOn_Off = new QLabel(this);

  QScrollArea* containTableList = new QScrollArea(this);
  QWidget* widgetScroll = new QWidget(this);
  layoutInScrollArea = new QVBoxLayout(this);

  widgetStack = new QStackedWidget(this);
  QPushButton* addTable = new QPushButton(tr("NewTable"));

  layout->addWidget(runningTable, 0, 0, 1, 2);
  layout->addWidget(containStatu, 0, 3, Qt::AlignRight);
  containStatu->setLayout(layoutStatu);
  layoutStatu->addWidget(dataOn_Off);
  layoutStatu->addWidget(iconOn_Off);
  layout->addWidget(containTableList, 1, 0);
  containTableList->setWidget(widgetScroll);
  widgetScroll->setLayout(layoutInScrollArea);
  layout->addWidget(addTable, 2, 0);
  layout->addWidget(widgetStack, 1, 1, 2, 3);

  layoutStatu->setAlignment(Qt::AlignRight);
  layoutInScrollArea->setAlignment(Qt::AlignTop);
  containTableList->setFixedWidth(this->width() * 2);
  containTableList->setWidgetResizable(true);

  if (ItemDAO::getInstance()->isDatableOnline())
  {
    iconOn_Off->setPixmap(SingleData::getInstance()->getPixmap("onCircle"));
    dataOn_Off->setText("On");
  }
  else
  {
    iconOn_Off->setPixmap(SingleData::getInstance()->getPixmap("offCircle"));
    dataOn_Off->setText("Off");
  }
  runningTable->setText(ItemDAO::getInstance()->getCurrentTable());
  connect(addTable, SIGNAL(clicked()), this, SLOT(createNewTable()));

  QStringList tableList = ItemDAO::getInstance()->getTablesList();
  int sizeList = (int)tableList.size();
  for (int i = 0; i < sizeList; i++)
  {
    addTableToList(tableList.at(i));
  }
};

void Database::addTableToList(QString tableName)
{
  QPushButton* buttonTable = new QPushButton(tableName, this);
  layoutInScrollArea->addWidget(buttonTable);
  createTableWidgets(tableName);

  buttonTable->setObjectName(tableName);
  buttonList.push_back(buttonTable);
  connect(buttonTable, SIGNAL(clicked()), this, SLOT(setWidgetToDisplay()));
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
  deleteDB->setObjectName(tableName);
  displayTable->setModel(ItemDAO::getInstance()->getQuerryModel(tableName));
  displayTable->show();

  widgetList.insert({tableName, mainTableWidget});
  displayTable->resizeColumnsToContents();

  connect(loadDB, SIGNAL(clicked()), this, SLOT(loadNewTable()));
  connect(deleteDB, SIGNAL(clicked()), this, SLOT(deleteTableConfirm()));
}

void Database::setWidgetToDisplay()
{

  widgetStack->setCurrentIndex(widgetStack->indexOf(widgetList.at(qobject_cast<QPushButton*>(sender())->text())));
}

void Database::loadNewTable()
{
  QString newTableName = sender()->objectName();
  ItemDAO::getInstance()->loadDBToItemList(newTableName);
  runningTable->setText(newTableName);
}

void Database::createNewTable()
{
  NewTable* table = new NewTable(this);
  connect(table, SIGNAL(transfertNewTable(QString, QString)), this, SLOT(connectNewTable(QString, QString)));
  table->exec();
}

void Database::connectNewTable(QString name, QString password)
{
  ItemDAO::getInstance()->setNewTable(name, password);
  addTableToList(name);
  sortItemList();
}

void Database::deleteTableConfirm()
{
  QString tableName = sender()->objectName();
  auto result{QMessageBox::question(this, tr("Valid deletion"), tr("Are you sure to want to delete ") + tableName + ".", QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No, QMessageBox::StandardButton::No)};

  if (result == QMessageBox::Yes)
  {
    widgetStack->setCurrentIndex(0);

    if (tableName == ItemDAO::getInstance()->getCurrentTable())
    {
      ItemDAO::getInstance()->loadDBToItemList("");
    }

    ItemDAO::getInstance()->deleteTable(tableName);

    widgetStack->removeWidget(widgetList.at(tableName));

    delete widgetList.at(tableName);
    widgetList.at(tableName) = nullptr;
    widgetList.erase(tableName);

    delete buttonList.at(0);
    buttonList.at(0) = nullptr;
    buttonList.erase(buttonList.begin());

    sortItemList();
  }
}

void Database::sortItemList()
{
  QStringList listTable = ItemDAO::getInstance()->getTablesList();
  int listSize = (int)listTable.size();
  for (int i = 0; i < listSize; i++)
  {
    buttonList.at(i)->setText(listTable.at(i));
  }
}

Database::~Database()
{
}
