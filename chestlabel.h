/**************************************************************************
**
**   chestlabel.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef CHESTLABEL_H
#define CHESTLABEL_H

#include "chests.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "ui_ulmainwindow.h"
#include "world.h"
#include "worldgenerator.h"
#include "llama.h"
#include <QLabel>
using namespace std;

class Chest;

class ChestLabel: public QLabel
{
public:
    Chest *chest;

    //constructor
    ChestLabel(QWidget *parent, Chest *_chest):QLabel(parent), chest(_chest) {}

    //getter method
    Chest* getChest() { return chest; }

    //setter method
    void setChest(Chest *_chest) { chest = _chest; }
};

#endif // CHESTLABEL_H
