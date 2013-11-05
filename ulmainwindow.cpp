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
#include <QString>

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


void ULMainWindow::on_easyStartButton_clicked()
{
/*
 *all the clicking - drag llama around the screen
 *click to open chest
 *keyboard input from user*/

    LlamaStats *llamaStats = new LlamaStats();
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
    TreasureChest *chest = new TreasureChest(false, 't', 200);
    chestLabel = new ChestLabel(ui->widgetGame, chest);
    QPixmap *chestImage = new QPixmap(":/images/download.jpg");
    chestLabel->setPixmap(*chestImage);
    chestLabel->setGeometry(QRect(100,100,90,150));
    chestLabel->show();

    //Disable so user cant spam-click llamas
    ui->easyStartButton->setEnabled(false);
    ui->easyStartButton->setStyleSheet("color: rgb(150, 150, 150);");
    ui->hardStartButton->setEnabled(false);
    ui->hardStartButton->setStyleSheet("color: rgb(150, 150, 150);");
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
        if(chestLabel->pos().x()-llamaLabel->pos().x()<15 && chestLabel->pos().x()-llamaLabel->pos().x()>-15) {
            if(chestLabel->pos().y()-llamaLabel->pos().y()<15 && chestLabel->pos().y()-llamaLabel->pos().y()>-15) {
                oKey=true;
                qDebug() << "O key success! It matched!";
                if (chestLabel->chest->getEmpty() == false) {
                    //open treasure chest
                    if (chestLabel->chest->getType() == 't') {
                        int newPesos = dynamic_cast<TreasureChest*>(chestLabel->chest)->getPesos();
                        qDebug() << "pesos:                 " << newPesos;
                        //apply pesos
                        llamaStats->setPesos(llamaStats->getPesos() + newPesos);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    } else if (chestLabel->chest->getType() == 'e') {
                        int lostLives = dynamic_cast<EnemyChest*>(chestLabel->chest)->getLivesLost();
                        qDebug() << "lost lives:                 " << lostLives;
                        //apply lost lives
                        llamaStats->setLives(llamaStats->getLives() + lostLives);
                        ui->labelPesos->setText("Lives: " + QString::number(llamaStats->getLives()));
                    } else if (chestLabel->chest->getType() == 'r') {
                        //ask riddle
                        //if riddle is correct,
                        llamaStats->setPesos(llamaStats->getPesos() + 200);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    }
                }
                //set chest to empty
                chestLabel->chest->setEmpty(true);
            }
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

void ULMainWindow::on_hardStartButton_clicked()
{

}
