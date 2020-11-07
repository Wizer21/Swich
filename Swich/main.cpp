#include "Swich.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
  srand(time(NULL));
  QApplication a(argc, argv);
  QPixmap pix(":/Swich/SwichLogo.png");
  pix = pix.scaled(50, 50);
  a.setWindowIcon(QIcon(pix));
  Swich w;
  w.show();
  return a.exec();
}
