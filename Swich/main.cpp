#include "Swich.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
  srand(time(NULL));
  QApplication a(argc, argv);
  Swich w;
  w.show();
  return a.exec();
}
