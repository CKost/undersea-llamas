/**************************************************************************
**
**   stateengine.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#include "stateengine.h"
#include "riddle.h"
#include <iostream>
#include <fstream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QTimer>

using namespace std;

StateEngine StateEngine::inst;

StateEngine* StateEngine::instance() { return &inst; }

StateEngine::StateEngine() : clock(this)
{
    clock.setInterval(50);
    QThread* thread = new QThread();
    clock.moveToThread(thread);
    connect(thread, SIGNAL(started()), &clock, SLOT(start()));
    connect(&clock,&QTimer::timeout, this, &StateEngine::on_timer_timeout);
    thread->start();
}

void StateEngine::saveToFile(QString filename)
{
    ofstream rvr(filename.toStdString().c_str());
    rvr << "[ULState File v1.0]" << endl; //Important: this signature is used for validation.
    rvr << "beginllamas" << endl;
    for(int i = 0; i<llamas.size(); ++i)
    {
        Llama* llama = llamas.at(i);
        //<id>:<x>,<y>:<health>:<pesos>:<dumblevel>:<facing>:<optional username>
        rvr << i << ":" << llama->getX() << "," << llama->getY() << ":" << llama->getPunish() <<
               ":" << llama->getPesos() << ":" << llama->getDumbLevel() << ":" << llama->getDir() <<
               ":" << llama->getUsername().toStdString() << endl;
    }
    rvr << "endllamas" << endl;
    rvr << currentWorldFile << endl;
    World* wrld = World::instance();
    for(int x = 0; x < wrld->getSize(); ++x)
    {
        for(int y = 0; y < wrld->getSize(); ++y)
        {
            WorldCell* cell = wrld->getCell(x,y);
            if(cell->getChest()->empty)
                rvr << x << " " << y << endl;
        }
    }
    rvr.close();
}

void StateEngine::loadFromFile(QString filename)
{
    QFile file (filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw "file load error";
    QTextStream in(&file);

    bool processingLlamas = false, isFirstLine = true, processingChests = false;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(isFirstLine)
        {
            if(line != "[ULState File v1.0]")
            throw "Whoa dude, that's not a legit state file. Check it before you wreck it next time please.";
            else
            {
                isFirstLine = false;
                continue;
            }
        }
        if(!isFirstLine && line == "beginllamas")
        {
            processingLlamas = true;
            continue;
        }
        if(processingLlamas)
        {
            if(line == "endllamas")
            {
                processingLlamas = false;
                continue;
            }
            QStringList splitline = line.split(":");
            int id = splitline[0].toInt();
            int x = splitline[1].split(",")[0].toInt();
            int y = splitline[1].split(",")[1].toInt();
            int health = splitline[2].toInt();
            int pesos = splitline[3].toInt();
            int dumbLevel = splitline[4].toInt();
            int facing = splitline[5].toInt();
            QString username = QString(splitline[6]);   //formerly splitline[6].toInt();
            Llama* llama = new Llama(x,y,facing,health,pesos);
            llama->setDumbLevel(dumbLevel);
            llama->setUsername(username);
            llamas.push_back(llama);
        }
        if(!isFirstLine && !processingLlamas && !processingChests && line != "beginllamas")
        {
            currentWorldFile = line.toStdString();
            World::loadFromFile(line);
            processingChests = true;
            continue;
        }
        if(processingChests)
        {
            QStringList splitline = line.split(" ");
            int x = splitline[0].toInt();
            int y = splitline[1].toInt();
            World::instance()->getCell(x,y)->getChest()->empty = true;
        }
    }
}

//llama methods
Llama* StateEngine::getLlama(int id)
{
    return llamas.at(id);
}
void StateEngine::addLlama(QString username)
{
    Llama* llama = new Llama(0,0,0,3,0);
    llama->setUsername(username);
    llamas.push_back(llama);
}
void StateEngine::punishLlama(int llamaID, int livesToTake)
{
    Llama* llama = getLlama(llamaID);
    llama->setPunish(llama->getPunish()-livesToTake);
}
void StateEngine::payLlama(int llamaID, int pesosToGive)
{
    Llama* llama = getLlama(llamaID);
    llama->setPesos(llama->getPesos()+pesosToGive);
}
bool StateEngine::moveLlama(int llamaID, double x, double y)
{
    if(World::instance()->getCell((int)x,(int)y)->getTerrainType() != 0) return false;
    else
    {
        Llama* llama = getLlama(llamaID);
        llama->setX(int(x));
        llama->setY(int(y));
    }
}
void StateEngine::youAreTheWeakestLinkLlama(int llamaID)
{
    getLlama(llamaID)->setDumbLevel(getLlama(llamaID)->getDumbLevel() + 1);
}

//chest methods
void StateEngine::openTChest(int llamaID, double x, double y)
{
    TreasureChest* tchest = dynamic_cast<TreasureChest*>(World::instance()->getCell(x,y)->getChest());
    if (tchest == NULL || tchest->empty) { return; }
    else {
        payLlama(llamaID,tchest->pesos);
    }
}
void StateEngine::openEChest(int llamaID, double x, double y)
{
    EnemyChest* echest = dynamic_cast<EnemyChest*>(World::instance()->getCell(x,y)->getChest());
    if (echest == NULL || echest->empty) { return; }
    else {
        punishLlama(llamaID,echest->damage);
    }
}
void StateEngine::openRChest(int llamaID, double x, double y)
{
    RiddleChest* rchest = dynamic_cast<RiddleChest*>(World::instance()->getCell(x,y)->getChest());
    if (rchest == NULL || rchest->empty) { return; }
    else {
        QString riddleline = QString::fromStdString(riddleEngine.get_riddle());
        QStringList riddle = riddleline.split("%");
        currentRiddle = riddle.at(0);
        currentAnswer = riddle.at(1);
        emit askRiddle(currentRiddle,currentAnswer,rchest->pesos);
    }
}
/*void StateEngine::openChest(int llamaID, double x, double y)
{
    Chest* chest = World::instance()->getCell(x,y)->getChest();
    if(chest == NULL || chest->empty) return;
    else
    {
        TreasureChest* tchest = dynamic_cast<TreasureChest*>(chest);
        if(tchest != NULL) payLlama(llamaID,tchest->pesos);
        EnemyChest* echest = dynamic_cast<EnemyChest*>(chest);
        if(echest != NULL) punishLlama(llamaID,echest->damage);
        RiddleChest* rchest = dynamic_cast<RiddleChest*>(chest);
        if(rchest != NULL)
        {
            QString riddleline = QString::fromStdString(riddleEngine.get_riddle());
            QStringList riddle = riddleline.split("%");
            currentRiddle = riddle.at(0);
            currentAnswer = riddle.at(1);
            emit askRiddle(currentRiddle,currentAnswer,rchest->pesos);
        }
    }
}*/

void StateEngine::on_timer_timeout()
{
    emit tick(++numTicks);
}
