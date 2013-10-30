/**************************************************************************
**
**   llama.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef LLAMA_H
#define LLAMA_H

#include "chests.h"
#include "riddle.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include <iostream>
#include <cstring>
#include <QString>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;

class Llama
{
private:
    //Location takes <x,y> coords
    int x,y;
    //Direction direction player facing
    int dir;
    //Counter of Llama's lives remaining
    int hp;
    //Pesos, count of points gathered by Llama. Also the score which will be called at the end to update hiscores
    int pesos;
    //Punishment, bad stuff happens. In terms of X amount of life lost
    int punish;
    //Number of dunce caps to draw on the llama.
    int dumbLevel;
    //Username of the player controlling the llama.
    QString username;

public:
    //Constructor
    Llama(int _x,int _y,int _dir,int _hp,int _pesos):x(_x),y(_y),dir(_dir),hp(_hp),pesos(_pesos){}

    //Get Methods
    int getX() {return x;}
    int getY() {return y;}
    int getDir() {return dir;}
    int getHP() {return hp;}
    int getPesos() {return pesos;}
    int getPunish() {return punish;}
    int getDumbLevel() {return dumbLevel;}
    QString getUsername() {return username;}

    //Set Methods
    void setX(int newX){x=newX;}
    void setY(int newY){y=newY;}
    void setDir(int newDir){dir=newDir;}
    void setHP(int newHP){hp=newHP;}
    void setPesos(int newPesos){pesos=newPesos;}
    void setPunish(int newPunish){punish=newPunish;}
    void setDumbLevel(int newDumbLevel) {dumbLevel = newDumbLevel;}
    void setUsername(QString newUserName) {username = newUserName;}

};

#endif // LLAMA_H
