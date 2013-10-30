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

    virtual int openChest(Llama* llama) {}
    virtual bool getChestStatus() { return this->empty; }
    virtual void setChestStatus(bool x) { empty = x; }
};

class TreasureChest: public Chest {
public:
    int pesos;
    int openChest(Llama* llama) {
        return pesos;
    }
};

class EnemyChest: public Chest {
public:
    int damage;
    int openChest(Llama* llama) {
        return (damage * -1);
    }
};

class RiddleChest: public Chest {
public:
    int riddleNum;
    int openChest(Llama* llama) {
        return 0;
    }
};

#endif // CHESTS_H
