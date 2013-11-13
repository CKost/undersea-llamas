/**************************************************************************

**   ulmainwindow.cpp
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/
#include "moviedisplay.h"
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
#include <QtGui>
#include <QLineEdit>
#include <QMouseEvent>
#include <QMainWindow>
#include <QInputDialog>
#include <QPixmap>

ULMainWindow::ULMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ULMainWindow)
{
    ui->setupUi(this);
    connect(StateEngine::instance(), &StateEngine::tick, this, &ULMainWindow::gameUpdate);
    connect(StateEngine::instance(), &StateEngine::askRiddle,this, &ULMainWindow::disRiddle); //Constructor for riddle showing, added 11/12
    currentUser = "LazDude";
    playerID = -1;
    gameStarted = false;
    gameOver = true;
    aKey = false; wKey = false; sKey = false; dKey = false;
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
    if (ui->labelLogo->isVisible()) {ui->labelLogo->setVisible(false);}
    StateEngine::instance()->loadFromFile(":/textfiles/statefile.ulstate");
    gameStarted = true;
    gameOver = false;
    //Disable so user cant spam-click llamas
    ui->easyStartButton->setEnabled(false);
    ui->easyStartButton->setStyleSheet("color: rgb(150, 150, 150);");
    ui->hardStartButton->setEnabled(false);
    ui->hardStartButton->setStyleSheet("color: rgb(150, 150, 150);");
}

void ULMainWindow::on_hardStartButton_clicked()
{
    if (ui->labelLogo->isVisible()) {ui->labelLogo->setVisible(false);}
    StateEngine::instance()->loadFromFile(":/textfiles/hardstate.ulstate");
    gameStarted = true;
    gameOver = false;
    //Disable keys so user cant spam-click llamas
    ui->easyStartButton->setEnabled(false);
    ui->easyStartButton->setStyleSheet("color: rgb(150, 150, 150);");
    ui->hardStartButton->setEnabled(false);
    ui->hardStartButton->setStyleSheet("color: rgb(150, 150, 150);");

}

void ULMainWindow::keyPressEvent(QKeyEvent *keyevent)
{

    if(keyevent->key() == Qt::Key_W) {
        wKey = true;
        qDebug() << "W key pressed.";
    }
    if(keyevent->key() == Qt::Key_A) {
        aKey = true;
        qDebug() << "A key pressed.";
    }
    if(keyevent->key() == Qt::Key_S) {
        sKey = true;
        qDebug() << "S key pressed.";
    }
    if(keyevent->key() == Qt::Key_D) {
        dKey = true;
        qDebug() << "D key pressed.";
    }
    if(keyevent->key() == Qt::Key_O) {
        oKey = true;
        qDebug() << "O key pressed.";
    }
}
void ULMainWindow::disRiddle(QString riddle, QString anwser, int pesos)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Riddle"),
                                             (riddle), QLineEdit::Normal,
                                             tr("Type in Answer :)"), &ok);
    if(ok && text==anwser)
    {

        MovieDisplay dlg;
        dlg.setGeometry(QRect(this->x()+this->width()/2-100,this->y()+this->height()/2-65,200,160));
        dlg.exec();

        StateEngine::instance()->payLlama(playerID,pesos);
    }
    else
    {
        //QMessageBox msgBox;
       // msgBox.information(this,"Incorrect Anwser","You anwsered it incorrectly"); //If just want basic messagebox, no image
            QMessageBox about;

            about.setInformativeText("Riddle solution was incorrect.");
            about.setStandardButtons(QMessageBox::Ok);
            about.setIconPixmap(QPixmap("://images/llamaMAD.png"));
            about.setDefaultButton(QMessageBox::Ok);
            about.setGeometry(QRect(this->x()+this->width()/4.5,this->y()+this->height()/4.5,90,140));
            about.show();
            about.exec();
    }
}

void ULMainWindow::gameUpdate(int elapsedTicks)
{
    if(!gameStarted) return;
    if(elapsedTicks % 100 == 0)
    qDebug() << "Tick! " << elapsedTicks << " ticks elapsed.";
    //This is going to be slightly messy, and for that I apologise.
    StateEngine *se = StateEngine::instance();
    World *world = World::instance();
    //Get the player's llama from the state engine, and make it our very own.
    if(playerID == -1)
    {
        for(int i = 0; i < se->getLlamaCount(); ++i)
        {
            if(se->getLlama(i)->getUsername() == currentUser)
                playerID = i;
        }
    }

    Llama* llama = se->getLlama(playerID);

    //Move llama if necessary.
    if(aKey && llama->getX() > -1)               se->moveLlama(playerID, llama->getX() - 1, llama->getY());
    if(dKey && llama->getX() < world->getSize()) se->moveLlama(playerID, llama->getX() + 1, llama->getY());
    if(wKey && llama->getY() > -1)               se->moveLlama(playerID, llama->getX(), llama->getY() - 1);
    if(sKey && llama->getY() < world->getSize()) se->moveLlama(playerID, llama->getX(), llama->getY() + 1);

    if(oKey && world->getCell(llama->getX(),llama->getY())->getChest() != NULL)
    {
        qDebug() << "Treasure opening!";
        Chest* chest = world->getCell(llama->getX(),llama->getY())->getChest();
        TreasureChest* tchest = dynamic_cast<TreasureChest*>(chest);
        EnemyChest* echest = dynamic_cast<EnemyChest*>(chest);
        RiddleChest* rchest = dynamic_cast<RiddleChest*>(chest);
        if(tchest != NULL) se->openTChest(playerID,llama->getX(),llama->getY());
        if(echest != NULL) se->openEChest(playerID,llama->getX(),llama->getY());
        if(rchest != NULL) se->openRChest(playerID,llama->getX(),llama->getY());
    }

    ui->labelLife->setText("Lives: " + QString::fromStdString(to_string(llama->getLives())));
    if (llama->getLives() == 0 && gameOver == false) {
        //display homescreen and win message
        ui->labelLogo->setVisible(true);
        ui->easyStartButton->setEnabled(true);
        ui->easyStartButton->setStyleSheet("color: rgb(250, 250, 250);");
        ui->hardStartButton->setEnabled(true);
        ui->hardStartButton->setStyleSheet("");
        QMessageBox::warning(this, "Game over.", "Sorry, you opened one too many enemy chests! Maybe if you try again, you can get the pesos you need. ¡Buena suerte!");
        //display high scores
        /////////////////////
        //reset game
        StateEngine::instance()->loseLlama(this->playerID);
        gameOver = true;
        for (int i = 0; i < ui->widgetGame->children().size() - 1; i++) {
            delete ui->widgetGame->children().at(i);
        }
    }
    ui->labelPesos->setText("Pesos: " + QString::fromStdString(to_string(llama->getPesos())));
    if (llama->getPesos() >= 3000 && gameOver == false) {
        //display homescreen and win message
        ui->labelLogo->setVisible(true);
        ui->easyStartButton->setEnabled(true);
        ui->easyStartButton->setStyleSheet("color: rgb(250, 250, 250);");
        ui->hardStartButton->setEnabled(true);
        ui->hardStartButton->setStyleSheet("");
        QMessageBox::warning(this, "You won!", "¡Felicidades! Congratulations on collecting your treasure! Now get back to the surface and pay off your debt, or enjoy another dive!");
        //display high scores
        /////////////////////
        //reset game
        StateEngine::instance()->winLlama(this->playerID);
        gameOver = true;
        for (int i = 0; i < ui->widgetGame->children().size() - 1; i++) {
            delete ui->widgetGame->children().at(i);
        }
    }

    int worldWidth, worldHeight,cellWidth,cellHeight;
    worldWidth = ui->widgetGame->width();
    worldHeight = ui->widgetGame->height();
    cellWidth = worldWidth / world->getSize();
    cellHeight = worldHeight / world->getSize();

    for(int x = 0; x < world->getSize(); ++x)
    {
        for(int y = 0; y < world->getSize(); ++y)
        {
            WorldCell* cell = world->getCell(x,y);
            if(cell->getTerrainType() == OBSTACLE)
            {
                bool hasLabel = false;
                for(QObject* qo : ui->widgetGame->children()) //this line crashes the debugger if you step through, otherwise another line will crash the program.
                {
                    QLabel* ql = dynamic_cast<QLabel*>(qo);
                    if(ql->pos().x() == x * cellWidth && ql->pos().y() == y * cellHeight && dynamic_cast<ChestLabel*>(ql) == NULL) hasLabel = true;
                }
                if(!hasLabel)
                {
                    QLabel* ql = new QLabel(ui->widgetGame);
                    ql->setGeometry(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
                    ql->setPixmap(QPixmap(":/images/rock.png"));
                    ql->setScaledContents(true);
                    ql->updateGeometry();
                    ql->show();
                }
            }
            Chest* chest = cell->getChest();
            bool hasLabel = false;
            for(QObject* qo : ui->widgetGame->children())
            {
                ChestLabel *label = dynamic_cast<ChestLabel*>(qo);
                if(label == NULL) continue;
                if(label->chest == chest) hasLabel = true;
                TreasureChest* tchest = dynamic_cast<TreasureChest*>(label->chest);
                if(tchest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/chest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                RiddleChest* rchest = dynamic_cast<RiddleChest*>(label->chest);
                if(rchest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/riddlechest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                EnemyChest* echest = dynamic_cast<EnemyChest*>(label->chest);
                if(echest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/enemychest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                label->updateGeometry();
                label->show();
            }
            if(chest != NULL && !hasLabel)
            {
                ChestLabel *label= new ChestLabel(ui->widgetGame, chest);
                label->setGeometry(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
                label->setScaledContents(true);
                TreasureChest* tchest = dynamic_cast<TreasureChest*>(chest);
                if(tchest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/chest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                RiddleChest* rchest = dynamic_cast<RiddleChest*>(chest);
                if(rchest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/riddlechest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                EnemyChest* echest = dynamic_cast<EnemyChest*>(chest);
                if(echest != NULL)
                {
                    if(se->isCheatMode()) label->setPixmap(QPixmap(":/images/enemychest.png"));
                    else label->setPixmap(QPixmap(":/images/chest.png"));
                }
                label->updateGeometry();
                label->show();
            }
        }
    }
    // BEGIN LLAMA CONNECTOR
    for(int i = 0; i < se->getLlamaCount(); ++i)
    {
        //qDebug() << "In llama connector loop.";
        Llama* llama = se->getLlama(i);
        //qDebug() << "Llama " << i <<" has address " << llama << " and username " << llama->getUsername();
        bool hasLabel = false;
        for(QObject* qo : ui->widgetGame->children())
        {
            LlamaLabel* ll = dynamic_cast<LlamaLabel*>(qo);
            if(ll == NULL) continue;
            if(ll->getLlama() == llama)
            {
                ll->setGeometry(llama->getX()*cellWidth, llama->getY()*cellHeight,cellWidth,cellHeight);
                ll->updateGeometry();
                hasLabel = true;
               // qDebug() << "Already has label at " << llama->getX() << ", " << llama->getY();
            }
        }
        if(!hasLabel)
        {
            LlamaLabel* ll = new LlamaLabel(ui->widgetGame, llama);
            ll->setGeometry(llama->getX()*cellWidth, llama->getY()*cellHeight,cellWidth,cellHeight);
            ll->setPixmap(QPixmap(":/images/llama.png"));
            ll->setScaledContents(true);
            ll->updateGeometry();
            ll->show();
           // qDebug() << "Created label! Llama at " << llama->getX() << ", " << llama->getY() <<".";
        }
    }
}


void ULMainWindow::keyReleaseEvent(QKeyEvent *keyevent)
{
    if (keyevent->key()==Qt::Key_A)
        {
            //qDebug()<<"keyReleaseEvent";
            aKey=false;
         }

    if (keyevent->key()==Qt::Key_S)
        {
           //qDebug()<<"keyReleaseEvent";
            sKey=false;
         }

    if (keyevent->key()==Qt::Key_W)
        {
            //qDebug()<<"keyReleaseEvent";
            wKey=false;
         }

    if (keyevent->key()==Qt::Key_D)
        {
            //qDebug()<<"keyReleaseEvent";
            dKey=false;
         }

    if (keyevent->key()==Qt::Key_O)
        {
            //qDebug()<<"keyReleaseEvent";
            oKey=false;
         }

   }

void ULMainWindow::on_cheatButton_clicked()
{
    QMessageBox::information(this,"Warning!","Cheat mode activated. Cheaters never prosper; you have been warned.");
    if(StateEngine::instance()->isCheatMode())
        StateEngine::instance()->setCheatMode(false);
    else StateEngine::instance()->setCheatMode(true);
}

void ULMainWindow::on_btnLoadState_clicked()
{
    //if (gameStarted == false) {
        if (ui->labelLogo) {ui->labelLogo->deleteLater();}
        QString stuff = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("UL State file (*.ulstate)"));
        if(!stuff.isEmpty())
            StateEngine::instance()->loadFromFile(stuff);
        gameStarted = true;
        gameOver = false;
    //}
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
