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

/**
 * @brief The ChestLabel class represents a chest.
 *
 * ChestLabel is a visual representation of a Chest to display to the user.
 */
class ChestLabel: public QLabel
{
public:
    Chest *chest;

    /** ChestLabel constructor*/
    ChestLabel(QWidget *parent, Chest *_chest):QLabel(parent), chest(_chest) {}

    /**
     * Gets the pointer to the chest the label represents.
     * @return A pointer to the chest.
     */
    Chest* getChest() { return chest; }

    /** Sets the chest the label is representing.
     * @param _chest A pointer to the chest the label represents.
     */
    void setChest(Chest *_chest) { chest = _chest; }
};

#endif // CHESTLABEL_H
