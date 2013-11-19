/**************************************************************************
**
**   chests.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef CHEST_H
#define CHEST_H

#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "worldgenerator.h"
/**
 * @brief The Chest class is a base type for chests.
 *
 * Represents the data stored in each chest. Chest is an abstract type,
 * inherited by EnemyChest, TreasureChest, and RiddleChest.
 */
class Chest {
public:
    bool empty;

    /** Chest constructor*/
    Chest(){}
    Chest(bool _empty):empty(_empty){}

    /** Returns whether the chest is empty or full
     *@param none
     *@return whether the chest is <empty>
     */
    bool getEmpty() { return this->empty; }

    /** Sets the chset to empty or full
     *@param bool emptied
     *@return void
     */
    void setEmpty(bool emptied) { empty = emptied; }

    virtual int getPesos() { return 0; }
    virtual int getLivesLost() { return 0; }
};

/**
 * @brief The TreasureChest class stores treasure.
 *
 * TreasureChest is a Chest that stores pesos to give to the llama upon opening.
 */
class TreasureChest: public Chest {
public:
    int pesos;

    /** TreasureChest constructor*/
    TreasureChest(bool _empty = false, int _pesos = 500):Chest(_empty), pesos(_pesos){}

    /** Gets the number of pesos in the chest
     *@param none
     *@return int pesos
     */
    int getPesos() { return this->pesos; }
};

/**
 * @brief The EnemyChest class steals lives.
 *
 * EnemyChest is a Chest that stores lives to steal from the llama upon opening.
 * (Presumably, it does this via an elaborate Rube Goldberg machine involving
 * piranhas.)
 */
class EnemyChest: public Chest {
public:
    int livesLost;

    /** EnemyChest constructor*/
    EnemyChest(bool _empty = false, int _livesLost = 1):Chest(_empty), livesLost(_livesLost){}

    /** Gets the number of life losses in the chest
     *@param none
     *@return int livesLost
     */
    int getLivesLost() { return this->livesLost; }
};

/**
 * @brief The RiddleChest class asks the player a riddle.
 *
 * RiddleChest is a Chest that stores riddles to ask the player upon opening.
 * You do not want to know how many clones of Alex Trebek we had to make in
 * order to get these working.
 */
class RiddleChest: public Chest {
public:
    int pesos;

    /** RiddleChest constructor*/
    RiddleChest(bool _empty = false, int _pesos = 600):Chest(_empty), pesos(_pesos){}

    /**
     *Gets the number of pesos in the chest
     *@param none
     *@return int pesos
     */
    int getPesos() { return this->pesos; }

};

#endif // CHEST_H
