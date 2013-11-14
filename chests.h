/**************************************************************************
**
**   chests.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef CHESTS_H
#define CHESTS_H

#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "worldgenerator.h"

class Chest {
public:
    bool empty;

    //constructor
    Chest(){}
    Chest(bool _empty):empty(_empty){}

    //getter and setter methods
    bool getEmpty() { return this->empty; }
    void setEmpty(bool emptied) { empty = emptied; }
    virtual int getPesos() { return 0; }
    virtual int getLivesLost() { return 0; }
};

class TreasureChest: public Chest {
public:
    int pesos;

    //constructors
    TreasureChest(bool _empty = false, int _pesos = 500):Chest(_empty), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }
};

class EnemyChest: public Chest {
public:
    int livesLost;

    //constructors
    EnemyChest(bool _empty = false, int _livesLost = 1):Chest(_empty), livesLost(_livesLost){}

    //getter methods
    int getLivesLost() { return this->livesLost; }
};

class RiddleChest: public Chest {
public:
    int pesos;

    //constructors
    RiddleChest(bool _empty = false, int _pesos = 600):Chest(_empty), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }

};

#endif // CHESTS_H
