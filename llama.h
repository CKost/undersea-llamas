/**************************************************************************
**
**   llama.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef LLAMA_H
#define LLAMA_H

#include "riddle.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <QString>
#include <cstdlib>

using namespace std;

/**
 * @brief The Llama class stores a llama.
 *
 * Llama is a class holding the data for a llama.
 */
class Llama
{
private:
    //Location takes <x,y> coords
    int x,y;
    //Direction direction player facing
    int dir;
    //Counter of Llama's lives remaining
    int lives;
    //Pesos, count of points gathered by Llama. Also the score which will be called at the end to update hiscores
    int pesos;
    //Punishment, bad stuff happens. In terms of X amount of life lost
    int punish;
    //Number of dunce caps to draw on the llama
    int dumbLevel;
    //Username of the player controlling the llama
    QString username;

public:
    /** Llama constructor*/
    Llama(int _x,int _y,int _dir,int _lives,int _pesos):x(_x),y(_y),dir(_dir),lives(_lives),pesos(_pesos){}

    //getter methods
    /** Gets llama's x coordinate*/
    int getX() {return x;}
    /** Gets llama's y coordinate*/
    int getY() {return y;}
    /** Gets llama's direction*/
    int getDir() {return dir;}
    /** Gets llama's number of lives*/
    int getLives() {return lives;}
    /** Gets llama's number of pesos*/
    int getPesos() {return pesos;}
    /** Gets llama's llama's number of lives lost*/
    int getPunish() {return punish;}
    /** Gets llama's dumbLevel*/
    int getDumbLevel() {return dumbLevel;}
    /** Gets username of the person playing as the llama*/
    QString getUsername() {return username;}

    //setter methods
    /** Sets llama's x coordinate*/
    void setX(int newX){x=newX;}
    /** Sets llama's y coordinate*/
    void setY(int newY){y=newY;}
    /** Sets llama's direction*/
    void setDir(int newDir){dir=newDir;}
    /** Sets llama's number of lives*/
    void setLives(int newLives){lives=newLives;}
    /** Sets llama's number of pesos*/
    void setPesos(int newPesos){pesos=newPesos;}
    /** Sets llama's number of lives lost*/
    void setPunish(int newPunish){punish=newPunish;}
    /** Sets llama's dumbLevel*/
    void setDumbLevel(int newDumbLevel) {dumbLevel = newDumbLevel;}
    /** Sets player's (llama's) username*/
    void setUsername(QString newUserName) {username = newUserName;}
};

#endif // LLAMA_H
