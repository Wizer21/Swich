#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Contact.h"
#include "SingleData.h"
#include "Static.h"

class Chat : public QWidget
{
  Q_OBJECT

public:
  Chat(std::vector<Contact>& list);
  void displayText(int pos, QString text, int indexChat);

private slots:
  void clickedDinausor();
  void enterText();
  void setTextZone();
  void setBarPosition(int min, int max);

private:
  int textId1;
  int textId2;
  std::vector<Contact>* getListContact;
  QStackedWidget* chatZone;
  QLineEdit* text;
  void setChat();
  void setContactList(QGridLayout* layout);
  void loadAnswer();
  void testChat(int& idChat);
  std::vector<QString> answerStored;
};
