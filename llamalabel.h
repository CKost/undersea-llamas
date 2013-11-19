/**************************************************************************
**
**   llamalabel.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef LLAMALABEL_H
#define LLAMALABEL_H

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

class Llama;

class LlamaLabel: public QLabel
{
    Llama *llama;

public:
    /** LlamaLabel constructor*/
    LlamaLabel(QWidget *parent, Llama *_llama):QLabel(parent), llama(_llama) {}

    /** Gets a llama pointer
     *@param none
     *@return llama pointer
     */
    Llama* getLlama() { return llama; }

    /** Sets the label's llama pointer
     *@param Llama*
     *@return void
     */
    void setLlama(Llama *_llama) { llama = _llama; }
};

#endif // LLAMALABEL_H
