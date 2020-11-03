#include "Chat.h"

Chat::Chat(std::vector<Contact>& list)
{
  getListContact = &list;
  setChat();
}

void Chat::setChat()
{
  QGridLayout* layoutChat = new QGridLayout(this);

  this->setLayout(layoutChat);
  setContactList(layoutChat);
}

void Chat::setContactList(QGridLayout* layout)
{
  //List
  QWidget* widgetList = new QWidget(this);
  QVBoxLayout* listLayout = new QVBoxLayout(this);

  // Zone
  layout->addWidget(widgetList, 0, 0);
  widgetList->setLayout(listLayout);

  chatZone = new QStackedWidget(this);
  layout->addWidget(chatZone, 0, 1);

  // Text Zone
  QWidget* textZone = new QWidget(this);
  QHBoxLayout* layoutText = new QHBoxLayout(this);
  text = new QLineEdit(this);
  QPushButton* icon = new QPushButton(this);

  layout->addWidget(textZone, 1, 1);
  textZone->setLayout(layoutText);
  layoutText->addWidget(text);
  layoutText->addWidget(icon);
  icon->setIcon(QIcon(":/Swich/dino.png"));
  listLayout->setAlignment(Qt::AlignTop);

  for (int i = 0; i < getListContact->size(); i++)
  {
    //List
    QPushButton* pushContact = new QPushButton(getListContact->at(i).getName(), this);
    pushContact->setIcon(QIcon(getListContact->at(i).getPix()));

    listLayout->addWidget(pushContact);
    pushContact->setObjectName(QString::number(i));
    // Zone
    QScrollArea* areaChat = new QScrollArea(this);
    QWidget* widgetChat = new QWidget(this);
    QVBoxLayout* layoutArea = new QVBoxLayout(this);

    chatZone->addWidget(areaChat);
    areaChat->setWidget(widgetChat);
    widgetChat->setLayout(layoutArea);

    areaChat->setWidgetResizable(true);
    layoutArea->setObjectName(QString::number(i));
    layoutArea->setAlignment(Qt::AlignBottom);

    connect(pushContact, SIGNAL(clicked()), this, SLOT(setTextZone()));
  }

  connect(icon, SIGNAL(clicked()), this, SLOT(clickedDinausor()));
  connect(text, SIGNAL(returnPressed()), this, SLOT(enterText()));
}

void Chat::enterText()
{
  displayText(1, text->text());
  text->clear();
}

void Chat::displayText(int pos, QString text)
{
  QLabel* textDisplayed = new QLabel(text, this);
  QVBoxLayout* layoutBox = this->findChild<QVBoxLayout*>(QString::number(chatZone->currentIndex()));

  layoutBox->addWidget(textDisplayed);

  if (pos == 0)
  {
    textDisplayed->setAlignment(Qt::AlignLeft);
  }
  else
  {
    textDisplayed->setAlignment(Qt::AlignRight);
  }
}

void Chat::setTextZone()
{
  chatZone->setCurrentIndex(sender()->objectName().toInt());
}

void Chat::clickedDinausor()
{
  QLabel* iconClick = new QLabel(this);
  iconClick->setPixmap(QPixmap(":/Swich/dino.png"));
  QVBoxLayout* layoutBoxDino = this->findChild<QVBoxLayout*>(QString::number(chatZone->currentIndex()));
  layoutBoxDino->addWidget(iconClick);
  iconClick->setAlignment(Qt::AlignRight);
}
