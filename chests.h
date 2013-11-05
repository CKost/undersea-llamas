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
    char type;

    //constructor
    Chest(){}
    Chest(bool _empty, char _type):empty(_empty), type(_type){}

    //getter and setter methods
    bool getEmpty() { return this->empty; }
    void setEmpty(bool emptied) { empty = emptied; }
    char getType() { return this->type; }
    virtual int getPesos() { return NULL; }
    virtual int getLivesLost() { return NULL; }
};

class TreasureChest: public Chest {
public:
    int pesos;

    //constructors
    TreasureChest(){}
    TreasureChest(bool _empty, char _type, int _pesos):Chest(_empty, _type), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }
};

class EnemyChest: public Chest {
public:
    int livesLost;

    //constructors
    EnemyChest(){}
    EnemyChest(bool _empty, char _type, int _livesLost):Chest(_empty, _type), livesLost(_livesLost){}

    //getter methods
    int getLivesLost() { return this->livesLost; }
};

class RiddleChest: public Chest {
public:
    int pesos;

    //constructors
    RiddleChest(){}
    RiddleChest(bool _empty, char _type, int _pesos):Chest(_empty, _type), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }

};

#endif // CHESTS_H
