/**************************************************************************
**
**   ulmainwindow.cpp
**
**   This file copyright 2013 Alex Fischer.
**   Work done for CpS 111 at Bob Jones University.
**
**   You may use this file however you see fit, with one exception:
**   You may not pass this work off as your own.
**
**************************************************************************/

#include "ulmainwindow.hpp"
#include "ui_ulmainwindow.h"

ULMainWindow::ULMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ULMainWindow)
{
    ui->setupUi(this);
}

ULMainWindow::~ULMainWindow()
{
    delete ui;
}
