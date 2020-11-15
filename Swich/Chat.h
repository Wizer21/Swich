#pragma once
#include <qwidget.h>
#include "stdafx.h"
#include "Contact.h"
#include "SingleData.h"

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
  std::vector<Contact>* getListContact;
  QStackedWidget* chatZone;
  QLineEdit* text;
  void setChat();
  void setContactList(QGridLayout* layout);
  void displayText(int pos, QString text);
};
