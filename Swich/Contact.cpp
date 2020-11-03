#include "Contact.h"

Contact::Contact(QString addName, QString addPixMap)
{
  name = addName;
  picture = addPixMap;
}

QString Contact::getName()
{
  return name;
}

QString Contact::getPix()
{
  return picture;
}