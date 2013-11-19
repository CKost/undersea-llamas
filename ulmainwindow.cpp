/**************************************************************************

**   ulmainwindow.cpp
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "chest.h"
#include "llama.h"
#include "llamalabel.h"
#include "moviedisplay.h"
#include "networkengine.h"
#include "riddle.h"
#include "stateengine.h"
#include "ui_ulmainwindow.h"
#include "ulmainwindow.h"
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
#include <sstream>
#include <QtAlgorithms>

using namespace std;

ULMainWindow::ULMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ULMainWindow)
{
    ui->setupUi(this);
    connect(StateEngine::instance(), &StateEngine::tick, this, &ULMainWindow::gameUpdate);
    connect(StateEngine::instance(), &StateEngine::askRiddle,this, &ULMainWindow::riddler); //Constructor for riddle showing, added 11/12
    currentUser = "LazDude";
    playerID = -1;
    gameStarted = false;
    gameOver = true;
    aKey = false; wKey = false; sKey = false; dKey = false;
    NetworkEngine::instance()->tryConnect();
    NetworkEngine::instance()->getHiscoresFromServer();
}

ULMainWindow::~ULMainWindow()
{
    delete ui;
}

/** Displays QMessageBox with game instructions*/
void ULMainWindow::on_buttonInstructions_clicked()
{
    QMessageBox::information(this, "How to Play", "¡Hola!\n\
    Usted está una llama, y necesita dinero. Tiene que pagar su crédito de universidad muy rapidamente, \
y explora el oceánico para recoger tesoro. Su objetivo es recoger pesos para pagar su crédito de universidad.\n\n\
En inglés: Hi!\n\
    You\'re a llama, and you need money. You\'ve got to pay off your student loan quickly, \
and you\'re exploring the ocean floor in search of treasure. Your goal is to find pesos to pay off your student loan.\n\n\
How to play:\n\
    To begin a new game, click the \"Easy,\" \"Hard,\" or \"Random World\" button. \
Then, push the \"W\" key to move up, \"A\" to move left, \"S\" to move down, and \"D\" to move right. \
Push the \"O\" key to open a chest. The chest can hold contain treasure (lots of pesos), an enemy (that will steal one of your lives), \
or a riddle (that you need to answer correctly to get pesos). You need to collect enough pesos to win the game. \
Don\'t lose all your lives, and hurry! Your loan\'s interest is eating away at your money the longer you wait!\n\n\n\
Have fun!");
}

/** Begins basic game*/
void ULMainWindow::on_hardStartButton_clicked()
{
    QString user = usernameGrabber();
    if (ui->labelLogo->isVisible()) {ui->labelLogo->setVisible(false);}
    StateEngine::instance()->loadFromFile(":/textfiles/hardstate.ulstate");
    gameStarted = true;
    gameOver = false;
    //Disable keys so user cant spam-click llamas
    ui->btnCreateWorld->setEnabled(false);
    ui->btnCreateWorld->setStyleSheet("color: rgb(150, 150, 150);");
    ui->hardStartButton->setEnabled(false);
    ui->hardStartButton->setStyleSheet("color: rgb(150, 150, 150);");
}

/** Determines when a keyboard key is pressed*/
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

/** Provides riddle functionality*/
void ULMainWindow::riddler(QString riddle, QString anwser, int pesos)
{
    oKey = false;
    wKey = false;
    aKey = false;
    sKey = false;
    dKey = false;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Riddle"),
                                             (riddle), QLineEdit::Normal,
                                             tr(""), &ok);
    if(ok && text==anwser)
    {

        MovieDisplay dlg;
        dlg.setGeometry(QRect(this->x()+this->width()/2-100,this->y()+this->height()/2-65,200,160));
        dlg.exec();

        StateEngine::instance()->payLlama(playerID,pesos);
    } else {
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

/** Gets username at start of new game*/
QString ULMainWindow::usernameGrabber()
{
    oKey = false;
    wKey = false;
    aKey = false;
    sKey = false;
    dKey = false;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Username"),
                                         ("Enter your username: "), QLineEdit::Normal,
                                             tr(""), &ok);
    return text;
}

/** Updates the game; makes the player win or lose*/
void ULMainWindow::gameUpdate(int elapsedTicks)
{
    if(!gameStarted) return;
    if(elapsedTicks % 100 == 0)
    {
        qDebug() << "Tick! " << elapsedTicks << " ticks elapsed.";
        if(!StateEngine::instance()->isCheatMode() && playerID != -1)
            StateEngine::instance()->payLlama(playerID,-100);
    }

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

    ui->labelPesos->setText("Pesos: " + QString::fromStdString(to_string(llama->getPesos())));

    //lose the game via losing lives
    if (llama->getLives() == 0 && gameOver == false) {
        //display message
        QMessageBox::warning(this, "Game over.", "Sorry, you opened one too many enemy chests! Maybe if you try again, you can get the pesos you need. ¡Buena suerte!");
        //reset game
        StateEngine::instance()->loseLlama(this->playerID);
        resetGame();
    }

    //lose the game via losing all your pesos
    if (llama->getPesos() == 0 && gameOver == false) {
        //display message
        QMessageBox::warning(this, "Game over.", "Sorry, you got bankrupted by interest! Maybe if you try again, you can get the pesos you need. ¡Buena suerte!");
        //reset game
        StateEngine::instance()->loseLlama(this->playerID);
        resetGame();
    }

    //win the game
    if (((StateEngine::instance()->isCheatMode() && llama->getPesos() >= 1000) ||
            llama->getPesos() >= 3000) &&
            gameOver == false) {
        //display message
        QMessageBox::warning(this, "You won!", "¡Felicidades! Congratulations on collecting your treasure! Now get back to the surface and pay off your debt, or enjoy another dive!");
        //reset game
        StateEngine::instance()->winLlama(this->playerID);
        resetGame();
    }

    if (gameOver == false) {
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
}

/** Determines when a keyboard key is released*/
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

/** Turns on cheat mode*/
void ULMainWindow::on_cheatButton_clicked()
{
    QMessageBox::information(this,"Warning!","Cheat mode activated. Cheaters never prosper; you have been warned.");
    if(StateEngine::instance()->isCheatMode())
        StateEngine::instance()->setCheatMode(false);
    else StateEngine::instance()->setCheatMode(true);
}

/** Loads a game state from a file*/
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

/** Saves a game state to a file*/
void ULMainWindow::on_btnSaveState_clicked()
{
    QString stuff = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("UL State file (*.ulstate)"));
    if(!stuff.isEmpty())
        StateEngine::instance()->saveToFile(stuff);
}

/** Begins randomly generated game*/
void ULMainWindow::on_btnCreateWorld_clicked()
{
    QString user = usernameGrabber();
    QFile::remove("temp.ulworld");
    currentUser = user;
    WorldGenerator().generate("temp.ulworld");
    stringstream ss;
    ss << "[ULState File v1.0]" << endl;
    ss << "beginllamas" << endl;
    ss << "0:2,2:3:400:0:0:" << user.trimmed().toStdString() << endl;
    ss << "endllamas" << endl;
    ss << "temp.ulworld" << endl;
    if (ui->labelLogo->isVisible()) {ui->labelLogo->setVisible(false);}
    StateEngine::instance()->fromStateString(QString::fromStdString(ss.str()));
    gameStarted = true;
    gameOver = false;
    //Disable keys so user cant spam-click llamas
    ui->hardStartButton->setEnabled(false);
    ui->hardStartButton->setStyleSheet("color: rgb(150, 150, 150);");
    ui->btnCreateWorld->setEnabled(false);
    ui->btnCreateWorld->setStyleSheet("color: rgb(150,150,150);");

}

void ULMainWindow::resetGame()
{
    gameOver = true;
    gameStarted = false;
    qDeleteAll(ui->widgetGame->children());
    ui->labelLogo->setVisible(true);
    ui->btnCreateWorld->setEnabled(true);
    ui->btnCreateWorld->setStyleSheet("");
    ui->hardStartButton->setEnabled(true);
    ui->hardStartButton->setStyleSheet("");
    playerID = -1;
    currentUser = "LazDude";
}

/** Displays highscore list from server*/
void ULMainWindow::on_hiscoreBtn_clicked()
{
    StateEngine::instance()->scores.clear();
    NetworkEngine::instance()->getHiscoresFromServer();
    stringstream ss;

    for(Highscore* ptr : StateEngine::instance()->scores)
    {
        ss << ptr->printAScore().toStdString() << endl;
    }
    QString answer;
    answer = "We calculate your score\n\based on your number of pesos and lives remaining.\n";
    answer += "\n" + QString::fromStdString(ss.str());
    QMessageBox::information(this,"Hi-scores",QString::fromStdString(ss.str()));
}
