/**************************************************************************
**
**   ulmainwindow.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "chests.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "ui_ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include <QMessageBox>
#include <QLabel>
#include <iostream>
#include <QDebug>


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

//Instructions for the game
void ULMainWindow::on_buttonInstructions_clicked()
{
    QMessageBox::information(this, "How to Play", "Here are instructions on how to play the game.");
}

void ULMainWindow::on_startButton_clicked()
{
/*
 *all the clicking - drag llama around the screen
 *click to open chest
 *keyboard input from user*/

    QLabel*llama = new QLabel(ui->widgetGame);
    QPixmap * bob = new QPixmap("://lama.jpg");
    llama->setPixmap(*bob);
    llama->setGeometry(QRect(
         rand() % (ui->widgetGame->geometry().width() - 100),
         rand() % (ui->widgetGame->geometry().height() - 100),
         100, 20));
    llama->show();
}


//Logic behind how i think keypresses to move llama wll work
void keyPressEvent(QKeyEvent *keyevent)
{
    if (keyevent->key()==Qt::Key_W)
        {
            qDebug() << "W key pressed";
            SetPos(pnt,0,1);//Or some method call to move up
        }
    if (keyevent->key()==Qt::Key_A)
        {
            qDebug() << "W key pressed";
            SetPos(pnt,0,-1);//Or some method call to move down
        }
    if (keyevent->key()==Qt::Key_A)
        {
            qDebug() << "W key pressed";
            SetPos(pnt,-1,0);//Or some method call to move Left
        }
    if (keyevent->key()==Qt::Key_D)
        {
            qDebug() << "W key pressed";
            SetPos(pnt,1,0);//Or some method call to move Right
        }
}

void SetPos(QPoint pnt,int x,int y)
{
    llama->setX(pnt.x()+x);
    llama->setY(pnt.y()+y);
     this->move(mapToParent(ev->pos() - this->llama));
 }


void ULMainWindow::on_cheatButton_clicked()
{

}
