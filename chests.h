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

    virtual bool getChestStatus() { return this->empty; }
    virtual void setChestStatus(bool emptied) { empty = emptied; }
};

class TreasureChest: public Chest {
public:
    int pesos;
};

class EnemyChest: public Chest {
public:
    int damage;
};

class RiddleChest: public Chest {
public:
    int pesos;
};

#endif // CHESTS_H
