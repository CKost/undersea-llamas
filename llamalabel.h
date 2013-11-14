/**************************************************************************
**
**   llamalabel.h
**
**   This file copyright 2013 Team Crackpot.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef LLAMALABEL_H
#define LLAMALABEL_H

#include "chests.h"
#include "riddle.h"
#include "stateengine.h"
#include "ulmainwindow.h"
#include "ui_ulmainwindow.h"
#include "world.h
#include "worldgenerator.h"
#include "llama.h"
#include <QLabel>
using namespace std;

class Llama;

class LlamaLabel: public QLabel
{
    Llama *llama;

public:
    //constructor
    LlamaLabel(QWidget *parent, Llama *_llama):QLabel(parent), llama(_llama) {}

    //getter method
    Llama* getLlama() { return llama; }

    //setter method
    void setLlama(Llama *_llama) { llama = _llama; }
};

#endif // LLAMALABEL_H
