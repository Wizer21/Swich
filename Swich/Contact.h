#pragma once
#include "stdafx.h"

class Contact
{
public:
  Contact(QString addName, QString addPixMap);
  QString getName();
  QString getPix();

private:
  QString name;
  QString picture;
};
