#include "Swich.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "SingleData.h"

int main(int argc, char* argv[])
{
  srand(time(NULL));
  QApplication a(argc, argv);
  QPixmap splashMap(":/Swich/splashReducted.png");
  QSplashScreen splash(splashMap.scaled(1000, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  splash.show();

  SingleData* s = s->getInstance();
  QPixmap pix(":/Swich/SwichLogo.png");
  pix = pix.scaled(50, 50);
  a.setWindowIcon(QIcon(pix));
  Swich w;

  splash.finish(&w);
  w.show();
  return a.exec();
}
