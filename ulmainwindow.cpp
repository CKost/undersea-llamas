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
#include <QPoint>
#include <QWidget>

#include <QMouseEvent>
#include <QMainWindow>


ULMainWindow::ULMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ULMainWindow)
{
    ui->setupUi(this);
    connect(StateEngine::instance(), &StateEngine::tick, this, &ULMainWindow::gameUpdate);
}

ULMainWindow::~ULMainWindow()
{
    delete ui;
}

//Instructions for the game
void ULMainWindow::on_buttonInstructions_clicked()
{
    QMessageBox::information(this, "How to Play", "Wondering how to play this game? First, click Start Game; then, use the WASD keys on your keyboard to move your llama around the screen. Press O to open a chest.");
}


void ULMainWindow::on_startButton_clicked()
{
/*
 *all the clicking - drag llama around the screen
 *click to open chest
 *keyboard input from user*/
    //was QLabel
   llama = new QLabel(ui->widgetGame);
    QPixmap *image = new QPixmap(":/images/llama.png");
    llama->setPixmap(*image);
    llama->setGeometry(QRect(
         rand() % (ui->widgetGame->geometry().width() - 100),
         rand() % (ui->widgetGame->geometry().height() - 100),
         90, 150));
    llama->show();

    //Display a cool chest
     chest = new QLabel(ui->widgetGame);
     QPixmap *chestImage = new QPixmap(":/images/download.jpg");
     chest->setPixmap(*chestImage);
     chest->setGeometry(QRect(100,100,80,80));
     chest->show();

    ui->startButton->setEnabled(false); //Disable so user cant spam click llamas LOL


}






































//Logic behind how I think keypresses to move llama will work
void ULMainWindow::keyPressEvent(QKeyEvent *keyevent)
{
    qDebug() << "key pressed";

    if (keyevent->key()==Qt::Key_W)
        {
        qDebug() << "W key pressed";

        if(llama->pos().y()>0)
        {
            wKey=true;
            llama->move(llama->pos().x(),llama->pos().y()-10);
            llama ->updateGeometry();
        }
        }
    if (keyevent->key()==Qt::Key_S)
        {
            qDebug() << "S key pressed";
            if(llama->pos().y()<265)
            {
            sKey=true;
            llama->move(llama->pos().x(),llama->pos().y()+10);
            llama ->updateGeometry();
            }

        }
    if (keyevent->key()==Qt::Key_A)
        {
            qDebug() << "A key pressed";
            if(llama->pos().x()>10)
            {
              aKey=true;
              llama->move(llama->pos().x()-10,llama->pos().y());
              llama ->updateGeometry();
            }

        }
    if (keyevent->key()==Qt::Key_D)
        {
            qDebug() << "D key pressed";
            if(llama->pos().x()<345)
            {
              dKey=true;
              llama->move(llama->pos().x()+10,llama->pos().y());
              llama ->updateGeometry();
            }

        }
    if (keyevent->key()==Qt::Key_O)
        {
            qDebug() << "O key pressed";
            oKey=true;
            //Open treasure chest
        }
}

void ULMainWindow::gameUpdate(int elapsedTicks)
{
    qDebug() << "Tick! " << elapsedTicks << " ticks elapsed.";
  /*
    StateEngine *mov;
    mov=StateEngine::instance();
    double curX;
    double curY;
    int ID=0;
    if(aKey)
    {
    curX =mov->getLlama(0)->getX();
    curY=mov->getLlama(0)->getY()-10;
    }
     mov->moveLlama(ID,curX,curY);
    */
}


void ULMainWindow::keyReleaseEvent(QKeyEvent *keyevent)
{
    qDebug()<<"keyReleaseEvent";

    aKey=false;
    sKey=false;
    wKey=false;
    dKey=false;
    oKey=false;
}

void ULMainWindow::on_cheatButton_clicked()
{

}
