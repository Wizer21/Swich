#include "Tutorial.h"

Tutorial::Tutorial()
  : QDialog()
{
  isOpen = false;
  isDocked = true;
  this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Tutorial* Tutorial::instance = nullptr;

void Tutorial::tutorialOpened(int currentId, QPoint corner)
{
  isOpen = true;

  layout = new QGridLayout(this);
  isTitle = new QLabel(this);
  QLabel* dockLabel = new QLabel(tr("Dock"), this);
  QCheckBox* checkBox = new QCheckBox(this);
  containText = new QTextEdit(this);

  layout->addWidget(isTitle, 0, 0);
  layout->addWidget(dockLabel, 0, 1, Qt::AlignCenter);
  layout->addWidget(checkBox, 0, 2);
  layout->addWidget(containText, 1, 0, 1, 3);

  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 0);
  layout->setColumnStretch(2, 0);

  dockLabel->setContentsMargins(5, 5, 5, 5);
  checkBox->setContentsMargins(5, 5, 5, 5);

  dockLabel->setAlignment(Qt::AlignRight);

  titles.clear();
  titles.append(tr("Hub"));
  titles.append(tr("Analytics"));
  titles.append(tr("Sales"));
  titles.append(tr("Production"));
  titles.append(tr("Team"));
  titles.append(tr("Stock"));
  titles.append(tr("Chat"));
  titles.append(tr("Options"));
  titles.append(tr("Database"));

  listText.clear();
  listText.append(tr("From here you can access to your higher scores, some information about your last 7 iterations and the new month button !\n\n"
                     "By clicking the 'new month' button:\n"
                     "  - Factories will send their production to your 'sales' menu.\n"
                     "  - If you have a commercial they will send a part of your items to the cities automatically.\n"
                     "  - Cities will sell a part of their items stocks, getting helped by your team for this part.\n"
                     "  - Factories will send their production to your sales menu."));
  listText.append(tr("Here you can visualize your statistics evolution."));
  listText.append(tr("Here you are able to drag parts of your items stocks to the cities of your choice."));
  listText.append(tr("The list of your factories, with their level, production and upgrade increase possibilities are displayed here."));
  listText.append(tr("From here you can manage your team:\n"
                     "  - New: at each new iteration, someone will come and introduce themself to try to join your team.\n"
                     "  - Team: every member of your team will increase the items' sold quantities for your cities.\n"
                     "  - Commercial: your commercial will push a part of your items to your cities.\n"));
  listText.append(tr("Here is the review of all your items.\n"));
  listText.append(tr("If you are feeling lonely, you might find someone to chat somewhere here.\n"));
  listText.append(tr("From the option menu you can select options who will be loaded at each application launch.\n"));
  listText.append(tr("The database menu enables you to manage tables avaible online.\n"));

  containText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  containText->setAlignment(Qt::AlignTop);
  checkBox->setChecked(true);

  containText->adjustSize();
  this->setGeometry(QRect(corner, QSize(500, 500)));
  this->show();

  pageChanged(currentId);

  connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(boxCheched(int)));
}

void Tutorial::pageChanged(int idPage)
{
  if (!isOpen)
  {
    return;
  }

  QFont font = qApp->font();
  font.setPointSize(font.pointSize() * 1.5);
  isTitle->setFont(font);

  isTitle->setText(titles.at(idPage));
  containText->setText(listText.at(idPage));
}

void Tutorial::closeEvent(QCloseEvent* e)
{
  isOpen = false;
  delete layout;
  layout = nullptr;
}

void Tutorial::mooved(QPoint point)
{
  if (isDocked)
  {
    this->setGeometry(QRect(point, QSize(500, 500)));
  }
}

void Tutorial::boxCheched(int idStatus)
{
  isDocked = (idStatus == 2);
}

void Tutorial::moveEvent(QMoveEvent* event)
{
  if (isDocked)
  {
    QPoint point(this->geometry().x(), this->geometry().y());
    emit tutorialMooved(point);
  }
}

Tutorial::~Tutorial()
{
}
