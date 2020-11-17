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

private slots:
  void clickedDinausor();
  void enterText();
  void setTextZone();

private:
  int textId1;
  int textId2;
  std::vector<Contact>* getListContact;
  QStackedWidget* chatZone;
  QLineEdit* text;
  void setChat();
  void setContactList(QGridLayout* layout);
  void displayText(int pos, QString text);
  void loadAnswer();
  void testChat(int& idChat);
  std::vector<QString> answerStored;
};
