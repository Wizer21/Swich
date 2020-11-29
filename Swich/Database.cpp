#include "Database.h"

Database::Database(QWidget* parent, int addCurrentWidget)
  : QDialog(parent)
{
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setAttribute(Qt::WA_DeleteOnClose);
  currentWidget = addCurrentWidget;

  QGridLayout* mainLayout = new QGridLayout(this);
  iniDB(mainLayout);

  this->resize(900, 450);
  this->setObjectName("dialogData");
  applyStyleSheet();
}

void Database::iniDB(QGridLayout* layout)
{
  QWidget* containTitle = new QWidget(this);
  QHBoxLayout* layoutTitle = new QHBoxLayout(this);
  QLabel* running = new QLabel(tr("Running on"), this);
  runningTable = new QLabel("nameTable", this);

  QWidget* containStatu = new QWidget(this);
  QHBoxLayout* layoutStatu = new QHBoxLayout(this);
  QLabel* dataOn_Off = new QLabel(this);
  QLabel* iconOn_Off = new QLabel(this);
  errorMessage = new QLabel(this);

  QScrollArea* containTableList = new QScrollArea(this);
  QWidget* widgetScroll = new QWidget(this);
  layoutInScrollArea = new QVBoxLayout(this);

  widgetStack = new QStackedWidget(this);
  QPushButton* addTable = new QPushButton(tr("NewTable"));

  layout->addWidget(containTitle, 0, 0, 1, 2);
  containTitle->setLayout(layoutTitle);
  layoutTitle->addWidget(running);
  layoutTitle->addWidget(runningTable);
  layout->addWidget(containStatu, 0, 3);
  containStatu->setLayout(layoutStatu);
  layout->addWidget(errorMessage, 0, 2);
  layoutStatu->addWidget(dataOn_Off);
  layoutStatu->addWidget(iconOn_Off);
  layout->addWidget(containTableList, 1, 0, 1, 1);
  containTableList->setWidget(widgetScroll);
  widgetScroll->setLayout(layoutInScrollArea);
  layout->addWidget(addTable, 2, 0, 1, 1);
  layout->addWidget(widgetStack, 1, 1, 2, 3);

  layoutTitle->setAlignment(Qt::AlignLeft);
  layoutStatu->setAlignment(Qt::AlignRight);
  layoutInScrollArea->setAlignment(Qt::AlignTop);
  containTableList->setFixedWidth(this->width() * 2);
  containTableList->setWidgetResizable(true);

  addTable->setIcon(SingleData::getInstance()->getPixMapOnActualTheme("table"));
  addTable->setCursor(Qt::PointingHandCursor);

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

  QFont font = qApp->font();
  font.setPointSize(font.pointSize() * 1.5);

  runningTable->setFont(font);
  dataOn_Off->setFont(font);
  widgetStack->setObjectName("stackTable");
  addTable->setObjectName("addtable");
  errorMessage->setContentsMargins(0, 0, 500, 0);
};

void Database::addTableToList(QString tableName)
{
  QPushButton* buttonTable = new QPushButton(tableName, this);
  layoutInScrollArea->addWidget(buttonTable);
  createTableWidgets(tableName);
  buttonTable->setCursor(Qt::PointingHandCursor);

  if (ItemDAO::getInstance()->isLocked(tableName))
  {
    buttonTable->setIcon(SingleData::getInstance()->getPixmap("lockdark"));
  }

  buttonTable->setObjectName(tableName);
  buttonList.push_back(buttonTable);
  connect(buttonTable, SIGNAL(clicked()), this, SLOT(setWidgetToDisplay()));
}

void Database::createTableWidgets(QString tableName)
{
  QWidget* mainTableWidget = new QWidget(this);
  QGridLayout* mainLayoutTable = new QGridLayout(this);
  QLabel* displayTableName = new QLabel(tableName, this);
  QPushButton* loadDB = new QPushButton(tr("Load"), this);
  QPushButton* deleteDB = new QPushButton(tr("Delete"), this);
  QPushButton* addItem = new QPushButton(tr("Add Item"), this);
  QPushButton* deleteItem = new QPushButton(tr("Delete Item"), this);
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
  addItem->setObjectName(tableName);
  deleteItem->setObjectName(tableName);
  displayTable->setObjectName(tableName);

  displayTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  displayTable->setModel(ItemDAO::getInstance()->getQuerryModel(tableName));
  displayTable->show();

  QHeaderView* header = displayTable->horizontalHeader();
  header->setSectionResizeMode(QHeaderView::Stretch);
  header->setSectionResizeMode(QHeaderView::Interactive);

  widgetList.insert({tableName, mainTableWidget});
  displayTable->resizeColumnsToContents();

  loadDB->setCursor(Qt::PointingHandCursor);
  deleteDB->setCursor(Qt::PointingHandCursor);
  addItem->setCursor(Qt::PointingHandCursor);
  deleteItem->setCursor(Qt::PointingHandCursor);

  SingleData* data = SingleData::getInstance();
  loadDB->setIcon(data->getPixMapOnActualTheme("upload"));
  deleteDB->setIcon(data->getPixMapOnActualTheme("trash"));
  addItem->setIcon(data->getPixMapOnActualTheme("item"));
  deleteItem->setIcon(data->getPixMapOnActualTheme("itemdelete"));

  connect(loadDB, SIGNAL(clicked()), this, SLOT(loadNewTable()));
  connect(deleteDB, SIGNAL(clicked()), this, SLOT(deleteTableConfirm()));
  connect(addItem, SIGNAL(clicked()), this, SLOT(createItem()));
  connect(deleteItem, SIGNAL(clicked()), this, SLOT(deleteNewItem()));
}

void Database::setWidgetToDisplay()
{
  QString table = qobject_cast<QPushButton*>(sender())->text();

  if (ItemDAO::getInstance()->isLocked(table))
  {
    PassWord* passMessage = new PassWord(this, table);
    connect(passMessage, SIGNAL(transfertValidPassWord(QString)), this, SLOT(passwordValidated(QString)));
    passMessage->exec();
    return;
  }
  widgetStack->setCurrentIndex(widgetStack->indexOf(widgetList.at(table)));
}

void Database::passwordValidated(QString tableName)
{
  widgetStack->setCurrentIndex(widgetStack->indexOf(widgetList.at(tableName)));
  ItemDAO::getInstance()->isUnlocked(tableName);
  updateLockIcon();
}

void Database::loadNewTable()
{
  QString newTableName = sender()->objectName();
  if (newTableName == ItemDAO::getInstance()->getCurrentTable())
  {
    errorMessage->setText(tr("Table already loaded"));
    return;
  }
  errorMessage->setText("");

  ItemDAO::getInstance()->loadDBToLists(newTableName);
  runningTable->setText(newTableName);
  emit tableChanged();
}

void Database::createNewTable()
{
  NewTable* table = new NewTable(this);
  connect(table, SIGNAL(transfertNewTable(QString, QString)), this, SLOT(connectNewTable(QString, QString)));
  table->exec();
  errorMessage->setText("");
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
      ItemDAO::getInstance()->loadDBToLists("");
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

void Database::updateLockIcon()
{

  int listSize = (int)buttonList.size();
  for (int i = 0; i < listSize; i++)
  {
    if (ItemDAO::getInstance()->isLocked(buttonList.at(i)->text()))
    {
      buttonList.at(i)->setIcon(SingleData::getInstance()->getPixMapOnActualTheme("lock"));
    }
    else
    {
      buttonList.at(i)->setIcon(QIcon(""));
    }
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
  updateLockIcon();
}

void Database::createItem()
{
  CreateNewItem* newItem = new CreateNewItem(this, sender()->objectName());
  connect(newItem, SIGNAL(transfertNewItem(QString, QString, double, double)), this, SLOT(applyNewItem(QString, QString, double, double)));
  newItem->exec();

  errorMessage->setText("");
}

void Database::applyNewItem(QString table, QString name, double buyP, double sellP)
{
  ItemDAO::getInstance()->addItemToTable(table, name, buyP, sellP);
  QTableView* view = this->findChild<QTableView*>(table);
  view->setModel(ItemDAO::getInstance()->getQuerryModel(table));
  view->setSelectionBehavior(QAbstractItemView::SelectRows);

  ItemDAO::getInstance()->loadDBToLists(ItemDAO::getInstance()->getCurrentTable());
  emit tableChanged();
}

void Database::deleteNewItem()
{
  QString tableName = sender()->objectName();

  QTableView* view = this->findChild<QTableView*>(tableName);
  QModelIndexList indexesSelected = view->selectionModel()->selectedRows();

  if (indexesSelected.size() == 0)
  {
    errorMessage->setText(tr("No item selected"));
    return;
  }
  errorMessage->setText("");
  QStringList selectedItemList;
  for (int i = 0; i < indexesSelected.count(); i++)
  {
    QModelIndex index = indexesSelected.at(i);
    auto nameItem = view->model()->data(view->model()->index(index.row(), 0));
    selectedItemList.push_back(nameItem.toString());
  }

  QString allInOne = "\n";
  int sizeList = (int)selectedItemList.size();
  for (int i = 0; i < sizeList; i++)
  {
    allInOne += ("\n- " + selectedItemList.at(i));
  }

  auto result{QMessageBox::question(this, tr("Valid deletion"), tr("Are you sure to want to delete :") + allInOne, QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No, QMessageBox::StandardButton::No)};

  if (result == QMessageBox::Yes)
  {
    for (int i = 0; i < sizeList; i++)
    {
      ItemDAO::getInstance()->deleteItemToTable(tableName, selectedItemList.at(i));
    }
    view->setModel(ItemDAO::getInstance()->getQuerryModel(tableName));
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
  }
  ItemDAO::getInstance()->loadDBToLists(ItemDAO::getInstance()->getCurrentTable());
  emit tableChanged();
}

void Database::applyStyleSheet()
{
  QString currentTheme = Utils::getThemeOnActualWidget(currentWidget);

  this->setStyleSheet(QString(
                        "QPushButton {"
                        "background-color: #262626; "
                        "color: %1; "
                        "padding: 5px; "
                        "border: 2px solid transparent; "
                        "border-right: 2px solid %1; "
                        "border-bottom: 2px solid %1; "
                        "font-size: 18px;}"
                        "QPushButton::hover { "
                        "border: 0px solid transparent; "
                        "border-right : 0px solid %1; "
                        "border-bottom : 0px solid %1;}"
                        "QPushButton::pressed { "
                        "background-color: %1; "
                        "color: #262626; "
                        "padding: 5px; "
                        "border: 0px solid transparent;}")
                        .arg(currentTheme));
  runningTable->setStyleSheet(QString("color: %1;").arg(currentTheme));
}

void Database::closeEvent(QCloseEvent* e)
{
}

Database::~Database()
{
}
