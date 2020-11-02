#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Swich.h"

class Swich : public QMainWindow
{
    Q_OBJECT

public:
    Swich(QWidget *parent = Q_NULLPTR);

private:
    Ui::SwichClass ui;
};
