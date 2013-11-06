/**************************************************************************

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
#include <QFileDialog>
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
    Para comenzar un juego nuevo, haga clic en el botón «comenzar». \
Entonces, empuje la tecla «W» para mover arriba, «A» para mover a la izquierda, «S» para mover abajo, y «D» para mover al derecho. \
Empuje la tecla <<O>> para abrir un cofre. El cofre puede contener tesoro (muchos pesos), un enemigo (que va a matarse), \
o un acertijo (que necesita contestar correctamente para ganar pesos). Necesita recoger pesos suficientes para ganar el juego, pero no perda su vida mientras trata ganar.\n\n\
¡Diviértase!\n\n\n\
En inglés: Hi!\n\
    You need money. You\'ve got to pay off your student loan quickly, \
and you\'re exploring the ocean floor in search of treasure. Your goal is to find pesos to pay off your student loan.\n\n\
How to play:\n\
    To begin a new game, clic the \"Start Game\" button. \
Then, push the \"W\" key to move up, \"A\" to move left, \"S\" to move down, and \"D\" to move right. \
Push the \"O\" key to open a chest. The chest can hold contain treasure (lots of pesos), an enemy (that will kill you), \
or a riddle (that you need to answer correctly to get pesos). You need to collect enough pesos to win the game, but don\'t lose your life trying to win.\n\n\
Have fun!");
}


void ULMainWindow::on_easyStartButton_clicked()
{
/*
 *all the clicking - drag llama around the screen
 *click to open chest
 *keyboard input from user*/

    llamaStats = new LlamaStats(3, 0);
    ui->labelLife->setText("Lives: " + QString::number(llamaStats->getLives()));
    ui->labelPesos->setText("Pesos: 0");
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
    chestLabel->setGeometry(QRect(0,0,90,150));
    chestLabel->show();

    //Display a chest
    TreasureChest *chest2 = new TreasureChest(false, 't', 500);
    chestLabel2 = new ChestLabel(ui->widgetGame, chest2);
    QPixmap *chestImage2 = new QPixmap(":/images/download.jpg");
    chestLabel2->setPixmap(*chestImage2);
    chestLabel2->setGeometry(QRect(100,100,90,150));
    chestLabel2->show();

    //Display a chest
    EnemyChest *chest3 = new EnemyChest(false, 'e', 1);
    chestLabel3 = new ChestLabel(ui->widgetGame, chest3);
    QPixmap *chestImage3 = new QPixmap(":/images/download.jpg");
    chestLabel3->setPixmap(*chestImage3);
    chestLabel3->setGeometry(QRect(200,200,90,150));
    chestLabel3->show();

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
        char trash;
        if(chestLabel->pos().x()-llamaLabel->pos().x()<15 && chestLabel->pos().x()-llamaLabel->pos().x()>-15) {
            if(chestLabel->pos().y()-llamaLabel->pos().y()<15 && chestLabel->pos().y()-llamaLabel->pos().y()>-15) {
                oKey=true;
                qDebug() << "O key success! It matched!";
                trash = '1';
            }
        }
        if(chestLabel2->pos().x()-llamaLabel->pos().x()<15 && chestLabel2->pos().x()-llamaLabel->pos().x()>-15) {
            if(chestLabel2->pos().y()-llamaLabel->pos().y()<15 && chestLabel2->pos().y()-llamaLabel->pos().y()>-15) {
                oKey=true;
                qDebug() << "O key success! It matched!";
                trash = '2';
            }
        }
        if(chestLabel3->pos().x()-llamaLabel->pos().x()<15 && chestLabel3->pos().x()-llamaLabel->pos().x()>-15) {
            if(chestLabel3->pos().y()-llamaLabel->pos().y()<15 && chestLabel3->pos().y()-llamaLabel->pos().y()>-15) {
                oKey=true;
                qDebug() << "O key success! It matched!";
                trash = '3';
            }
        }
        if (oKey == true) {
            if (trash == '1') {
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
                        llamaStats->setLives(llamaStats->getLives() - lostLives);
                        ui->labelLife->setText("Lives: " + QString::number(llamaStats->getLives()));
                    } else if (chestLabel->chest->getType() == 'r') {
                        //ask riddle
                        //if riddle is correct,
                        llamaStats->setPesos(llamaStats->getPesos() + 200);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    }
                    //set chest to empty
                    chestLabel->chest->setEmpty(true);
                }
            } else if (trash == '2') {
                if (chestLabel2->chest->getEmpty() == false) {
                    //open treasure chest
                    if (chestLabel2->chest->getType() == 't') {
                        int newPesos = dynamic_cast<TreasureChest*>(chestLabel2->chest)->getPesos();
                        qDebug() << "pesos:                 " << newPesos;
                        //apply pesos
                        llamaStats->setPesos(llamaStats->getPesos() + newPesos);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    } else if (chestLabel2->chest->getType() == 'e') {
                        int lostLives = dynamic_cast<EnemyChest*>(chestLabel2->chest)->getLivesLost();
                        qDebug() << "lost lives:                 " << lostLives;
                        //apply lost lives
                        llamaStats->setLives(llamaStats->getLives() - lostLives);
                        ui->labelLife->setText("Lives: " + QString::number(llamaStats->getLives()));
                    } else if (chestLabel2->chest->getType() == 'r') {
                        //ask riddle
                        //if riddle is correct,
                        llamaStats->setPesos(llamaStats->getPesos() + 200);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    }
                    //set chest to empty
                    chestLabel2->chest->setEmpty(true);
                }
            } else if (trash == '3') {
                if (chestLabel3->chest->getEmpty() == false) {
                    //open treasure chest
                    if (chestLabel3->chest->getType() == 't') {
                        int newPesos = dynamic_cast<TreasureChest*>(chestLabel3->chest)->getPesos();
                        qDebug() << "pesos:                 " << newPesos;
                        //apply pesos
                        llamaStats->setPesos(llamaStats->getPesos() + newPesos);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    } else if (chestLabel3->chest->getType() == 'e') {
                        int lostLives = dynamic_cast<EnemyChest*>(chestLabel3->chest)->getLivesLost();
                        qDebug() << "lost lives:                 " << lostLives;
                        //apply lost lives
                        llamaStats->setLives(llamaStats->getLives() - lostLives);
                        ui->labelLife->setText("Lives: " + QString::number(llamaStats->getLives()));
                    } else if (chestLabel3->chest->getType() == 'r') {
                        //ask riddle
                        //if riddle is correct,
                        llamaStats->setPesos(llamaStats->getPesos() + 200);
                        ui->labelPesos->setText("Pesos: " + QString::number(llamaStats->getPesos()));
                    }
                    //set chest to empty
                    chestLabel3->chest->setEmpty(true);
                }
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
    QMessageBox::information(this,"Warning!","Cheat mode activated. Cheaters never prosper; you have been warned.");
}

void ULMainWindow::on_hardStartButton_clicked()
{

}

void ULMainWindow::on_btnLoadState_clicked()
{
    QString stuff = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("UL State file (*.ulstate)"));
    if(!stuff.isEmpty())
        StateEngine::instance()->loadFromFile(stuff);
}

void ULMainWindow::on_btnSaveState_clicked()
{
    QString stuff = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("UL State file (*.ulstate)"));
    if(!stuff.isEmpty())
        StateEngine::instance()->saveToFile(stuff);
}

void ULMainWindow::on_btnCreateWorld_clicked()
{
    QString stuff = QFileDialog::getSaveFileName(this, tr("Save file"), ".", tr("UL World File (*.ulworld)"));
    if(!stuff.isEmpty())
        WorldGenerator().generate(stuff);
}
