/**************************************************************************
**
**   chestlabel.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef CHESTLABEL_H
#define CHESTLABEL_H

#include "chest.h"
#include "llama.h"
#include "riddle.h"
#include "stateengine.h"
#include "ui_ulmainwindow.h"
#include "ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"

#include <QLabel>

using namespace std;

class Chest;

class ChestLabel: public QLabel
{
public:
    Chest *chest;

    /** ChestLabel constructor*/
    ChestLabel(QWidget *parent, Chest *_chest):QLabel(parent), chest(_chest) {}

    /** Gets a chest pointer
     *@param none
     *@return chest pointer
     */
    Chest* getChest() { return chest; }

    /** Sets the label's chest pointer
     *@param Chest*
     *@return void
     */
    void setChest(Chest *_chest) { chest = _chest; }
};

#endif // CHESTLABEL_H
