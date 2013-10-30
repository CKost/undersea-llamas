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

using namespace std;

StateEngine StateEngine::inst;

StateEngine StateEngine::instance() { return inst; }

vector<QString> StateEngine::getRiddle()
{
    throw "Dude, totally not implemented.";
    //TODO: GET CURT TO IMPLEMENT RIDDLE RETRIEVAL
}

void StateEngine::saveToFile(QString filename)
{
    ofstream rvr(filename.toWCharArray()); //change to filename.toWCharArray(wchar_t*));
    rvr << "[ULState File v1.0]" << endl; //Important: this signature is used for validation.
    rvr << "beginllamas" << endl;
    for(int i = 0; i<llamas.size(); ++i)
    {
        Llama* llama = llamas.at(i);
        //<id>:<x>,<y>:<health>:<pesos>:<dumblevel>:<facing>:<optional username>
        rvr << i << ":" << llama->getX() << "," << llama->getY() << ":" << llama->getPunish() <<
               ":" << llama->getPesos() << ":" << llama->getDumbLevel() << ":" << llama->getDir() <<
               ":" << llama->getUsername() << endl;
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
    ifstream rvr(filename.toWCharArray()); //change to filename.toWCharArray(wchar_t*));
    char *linechar = new char[100];
    bool processingLlamas = false,processingChests = false,isFirstLine = true;
    while(rvr.getline(linechar,100))
    {
        QString line (linechar);
        if(isFirstLine)
        {
            if(line != "[ULWorld File v1.0]")
            throw "Whoa dude, that's not a legit world file. Check it before you wreck it next time please.";
            else isFirstLine = false;
        }
        if(!isFirstLine && line == "beginllamas")
            processingLlamas = true;
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
        if(!isFirstLine && !processingLlamas && line != "beginllamas")
        {
            currentWorldFile = line.toStdString();
            World::loadFromFile(line);
            processingChests = true;
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
void StateEngine::addLlama(QString username)
{
    Llama* llama = new Llama(0,0,0,3,0);
    llama->setUsername(username);
    llamas.push_back(llama);
}
//void

