#include "Chat.h"

Chat::Chat(std::vector<Contact>& list)
{
  textId1 = 0;
  textId2 = 0;
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

  SingleData* getData = getData->getInstance();
  getData->addButtoonToAdaptOnTheme("dino", icon);

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

    pushContact->setCursor(Qt::PointingHandCursor);
    connect(pushContact, SIGNAL(clicked()), this, SLOT(setTextZone()));
    areaChat->setObjectName("scroll" + QString::number(i));
    areaChat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(areaChat->verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setBarPosition(int, int)));
  }

  loadAnswer();
  displayText(0, tr("Hey, welcome !"), chatZone->currentIndex());
  icon->setCursor(Qt::PointingHandCursor);
  connect(icon, SIGNAL(clicked()), this, SLOT(clickedDinausor()));
  connect(text, SIGNAL(returnPressed()), this, SLOT(enterText()));
}

void Chat::enterText()
{
  QString textEntered(text->text());
  if (textEntered.trimmed().size() == 0)
  {
    return;
  }

  displayText(1, textEntered, chatZone->currentIndex());
  switch (chatZone->currentIndex())
  {
    case 0:
      textId1++;
      testChat(textId1);
      break;
    case 1:
      textId2++;
      testChat(textId2);
      break;
  }

  text->clear();
}

void Chat::displayText(int pos, QString newText, int indexChat)
{
  QLabel* textDisplayed = new QLabel(newText, this);
  QVBoxLayout* layoutBox = this->findChild<QVBoxLayout*>(QString::number(indexChat));

  layoutBox->addWidget(textDisplayed);

  if (pos == 0)
  {
    textDisplayed->setAlignment(Qt::AlignLeft);
  }
  else
  {
    textDisplayed->setAlignment(Qt::AlignRight);
  }
  textDisplayed->setWordWrap(true);
  textDisplayed->show();
}

void Chat::setBarPosition(int min, int max)
{
  auto barArea = qobject_cast<QScrollBar*>(sender());
  barArea->setSliderPosition(max);
}

void Chat::setTextZone()
{
  chatZone->setCurrentIndex(sender()->objectName().toInt());
}

void Chat::clickedDinausor()
{
  QLabel* iconClick = new QLabel(this);
  iconClick->setPixmap(QPixmap(SingleData::getInstance()->getPixMapOnActualTheme("dino")));
  QVBoxLayout* layoutBoxDino = this->findChild<QVBoxLayout*>(QString::number(chatZone->currentIndex()));
  layoutBoxDino->addWidget(iconClick);
  iconClick->setAlignment(Qt::AlignRight);
}

void Chat::loadAnswer()
{
  answerStored.push_back(tr("Hey !"));
  answerStored.push_back(tr("You are actually on a showcase app !"));
  answerStored.push_back(tr("The sun bright !"));
  answerStored.push_back(tr("This application was made with C++ and the Qt library."));
  answerStored.push_back(tr("I made the logo with Photoshop."));
  answerStored.push_back(tr("You can found on my GitHub a first version of this concept under \"SimulationRevendeur\"."));
  answerStored.push_back(tr("Monstera are such beautiful plants !"));
  answerStored.push_back(tr("Do you like cookies ?"));
  answerStored.push_back(tr("Sorry, we are out of coffee."));
  answerStored.push_back(tr("You can found on my GitHub the developpement history of this app."));
}

void Chat::testChat(int& idChat)
{
  int chanceToDiaslap = idChat;
  while (chanceToDiaslap > 0)
  {
    if (Static::randZeroToVal(10) > 6)
    {
      displayText(0, answerStored.at(Static::randZeroToVal(answerStored.size())), chatZone->currentIndex());
      idChat = 0;
    }
    chanceToDiaslap--;
  }
}