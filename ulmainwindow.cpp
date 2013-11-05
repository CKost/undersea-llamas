+ /**************************************************************************
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
#include "llamalabel.h"
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
    QMessageBox::information(this, "How to Play", "¡Hola!\n\
        Necesita dinero. Tiene que pagar su crédito de universidad muy rapidamente, \
        y explora el oceánico para recoger tesoro. Su objetivo es recoger pesos para pagar su crédito de universidad.\n\n\
        Como jugar:\n\
        Para comenzar un juego nuevo, haga clic en el botón «comenzar».\
        Entonces, empuje la tecla «W» para mover arriba, «A» para mover a la izquierda, «S» para mover abajo, y «D» para mover al derecho.\
        Empuje la tecla <<O>> para abrir un cofre. El cofre puede contener tesoro (con muchos pesos), un enemigo (que va a matarse),\
        o un acertijo (que necesita contestar correctamente para ganar pesos).\
        ¡Diviértase!");
}


void ULMainWindow::on_startButton_clicked()
{
/*
 *all the clicking - drag llama around the screen
 *click to open chest
 *keyboard input from user*/

    Llama *llama = new Llama(0, 0, 0, 3, 100);
    llamaLabel = new LlamaLabel(ui->widgetGame, llama);
    QPixmap *image = new QPixmap(":/images/llama.jpg");
    llamaLabel->setPixmap(*image);
    //llamaLabel->setGeometry(QRect(200,100,90,150));
    llamaLabel->setGeometry(QRect(
         rand() % (ui->widgetGame->geometry().width() - 100),
         rand() % (ui->widgetGame->geometry().height() - 100),
         90, 150));
    llamaLabel->show();

    //Display a chest
    chest = new QLabel(ui->widgetGame);
    QPixmap *chestImage = new QPixmap(":/images/download.jpg");
    chest->setPixmap(*chestImage);
    chest->setGeometry(QRect(100,100,90,150));
    chest->show();

    ui->startButton->setEnabled(false); //Disable so user cant spam-click llamas
}


void ULMainWindow::keyPressEvent(QKeyEvent *keyevent)
{

    if (keyevent->key()==Qt::Key_W) {
        qDebug() << "W key pressed";
        if(llamaLabel->pos().y()>10) {
            wKey=true;
            llamaLabel->move(llamaLabel->pos().x(), llamaLabel->pos().y()-10);
            llamaLabel->updateGeometry();
        }
    }
    if (keyevent->key()==Qt::Key_S) {
        qDebug() << "S key pressed";
        if(llamaLabel->pos().y()<(ui->widgetGame->height()-llamaLabel->height()-10)) {
            sKey=true;
            llamaLabel->move(llamaLabel->pos().x(), llamaLabel->pos().y()+10);
            llamaLabel->updateGeometry();
        }
    }
    if (keyevent->key()==Qt::Key_A) {
        qDebug() << "A key pressed";
        if(llamaLabel->pos().x()>10) {
            aKey=true;
            llamaLabel->move(llamaLabel->pos().x()-10, llamaLabel->pos().y());
            llamaLabel->updateGeometry();
        }
    }
    if (keyevent->key()==Qt::Key_D) {
        qDebug() << "D key pressed";
        if(llamaLabel->pos().x()<(ui->widgetGame->width()-llamaLabel->width()-10)) {
            dKey=true;
            llamaLabel->move(llamaLabel->pos().x()+10, llamaLabel->pos().y());
            llamaLabel->updateGeometry();
        }
    }
    if (keyevent->key()==Qt::Key_O) {
        qDebug() << "O key pressed";
        if(chest->pos().x()==llamaLabel->pos().x()&&chest->pos().y()==llamaLabel->pos().y()) {
            oKey=true;
            //if (chest->getChestStatus != true) {
                //open treasure chest
                //apply pesos, lost lives, riddle
            //}
        }
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

    if (keyevent->key()==Qt::Key_A)
        {
            qDebug()<<"keyReleaseEvent";
            aKey=false;
         }

    if (keyevent->key()==Qt::Key_S)
        {
           qDebug()<<"keyReleaseEvent";
            sKey=false;
         }

    if (keyevent->key()==Qt::Key_W)
        {
            qDebug()<<"keyReleaseEvent";
            wKey=false;
         }

    if (keyevent->key()==Qt::Key_D)
        {
            qDebug()<<"keyReleaseEvent";
            dKey=false;
         }

    if (keyevent->key()==Qt::Key_O)
        {
            qDebug()<<"keyReleaseEvent";
            oKey=false;
         }

   }

void ULMainWindow::on_cheatButton_clicked()
{

}
