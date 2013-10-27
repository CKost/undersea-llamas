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
#include "world.h"
#include "worldgenerator.h"

class chest {
    int xLoc, yLoc;
    bool empty;
    virtual void openChest(Llama llama) {}
};

class treasureChest: public chest {
    int pesos;
    int openChest(Llama llama) {
        return pesos;
    }
};

class enemyChest: public chest {
    int damage;
    int openChest(Llama llama) {
        return (damage * -1);
    }
};

class riddleChest: public chest {
    int riddleNum;
    int openChest(Llama llama) {
        return 0;
    }
};

#endif // CHESTS_H
