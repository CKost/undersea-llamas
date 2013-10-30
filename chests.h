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
    virtual int getPesos() { return NULL; }
};

class TreasureChest: public Chest {
public:
    int pesos;

    //constructors
    TreasureChest(){}
    TreasureChest(bool _empty, int _pesos):Chest(_empty), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }
};

class EnemyChest: public Chest {
public:
    int damage;

    //constructors
    EnemyChest(){}
    EnemyChest(bool _empty, int _damage):Chest(_empty), damage(_damage){}

    //getter methods
    bool getDamage() { return this->damage; }
};

class RiddleChest: public Chest {
public:
    int pesos;

    //constructors
    RiddleChest(){}
    RiddleChest(bool _empty, int _pesos):Chest(_empty), pesos(_pesos){}

    //getter methods
    int getPesos() { return this->pesos; }
};

#endif // CHESTS_H
